#!/bin/bash

set -e
echo "################################################"
echo "#   Welcome to PAC Masternode's server setup   #"		
echo "################################################"
echo "" 
read -p 'Please provide the external IP: ' ipaddr
read -p 'Please provide masternode genkey: ' mnkey

while [[ $ipaddr = '' ]] || [[ $ipaddr = ' ' ]]; do
	read -p 'You did not provided an external IP, please provide one: ' ipaddr
	sleep 2
done

while [[ $mnkey = '' ]] || [[ $mnkey = ' ' ]]; do
	read -p 'You did not provided masternode genkey, please provide one: ' mnkey
	sleep 2
done

echo "###############################"
echo "#  Installing Dependencies    #"		
echo "###############################"
echo ""
echo "Running this script on Ubuntu 16.04 LTS is highly recommended (2GB RAM)"

sudo add-apt-repository -y ppa:bitcoin/bitcoin
sudo apt-get -y update
sudo apt-get -y install libminiupnpc-dev
sudo apt-get -y install libboost-all-dev 
sudo apt-get -y install build-essential
sudo apt-get -y install libtool
sudo apt-get -y install autotools-dev
sudo apt-get -y install automake pkg-config
sudo apt-get -y install libssl-dev
sudo apt-get -y install libevent-dev bsdmainutils
sudo apt-get -y install git
sudo apt-get -y install libzmq3-dev
sudo apt-get -y install libdb4.8-dev
sudo apt-get -y install libdb4.8++-dev
sudo apt-get -y install virtualenv
sudo apt-get -y install ufw
sudo apt-get -y install pwgen
sudo apt-get -y install jq


echo "###############################"
echo "#   Setting up the Firewall   #"		
echo "###############################"
sudo ufw status
sudo ufw disable
sudo ufw allow ssh/tcp
sudo ufw limit ssh/tcp
sudo ufw allow 7112/tcp
sudo ufw logging on
sudo ufw --force enable
sudo ufw status

sudo iptables -A INPUT -p tcp --dport '7112' -j ACCEPT

echo ""
echo "###############################"
echo "#      Get/Setup binaries     #"		
echo "###############################"
echo ""
wget "https://github.com/PACCommunity/PAC/releases/download/v0.12.2.3/PAC-v0.12.2.3-ubuntu-16.04-x64.tar.gz"
tar xvf 'PAC-v0.12.2.3-ubuntu-16.04-x64.tar.gz'
cp PAC-v0.12.2.3-ubuntu-16.04-x64/* ~/
cd ~/
rm PAC-v0.12.2.3-ubuntu-16.04-x64.tar.gz
rm -r PAC-v0.12.2.3-ubuntu-16.04-x64
currpath=$( pwd )
echo "Binaries got stored on: $currpath"
chmod +x paccoind
chmod +x paccoin-cli

echo "###############################"
echo "#     Configure the wallet    #"		
echo "###############################"
echo ""
echo "The .paccoincore folder will be created, if folder already exists, it will be replaced"
if [ -d ~/.paccoincore ]; then
	if [ -e ~/.paccoincore/paccoin.conf ]; then
		read -p "The file paccoin.conf already exists and will be replaced. do you agree [y/n]:" cont
		if [ $cont = 'y' ] || [ $cont = 'yes' ] || [ $cont = 'Y' ] || [ $cont = 'Yes' ]; then
			sudo rm ~/.paccoincore/paccoin.conf
			touch ~/.paccoincore/paccoin.conf
			cd ~/.paccoincore
		fi
	fi
else
	echo "Creating .paccoincore dir"
	mkdir -p ~/.paccoincore
	cd ~/.paccoincore
	touch paccoin.conf
fi

echo "Configuring the paccoin.conf"
echo "rpcuser=$(pwgen -s 16 1)" > paccoin.conf
echo "rpcpassword=$(pwgen -s 64 1)" >> paccoin.conf
echo "rpcallowip=127.0.0.1" >> paccoin.conf
echo "rpcport=7111" >> paccoin.conf
echo "externalip=$ipaddr" >> paccoin.conf
echo "port=7112" >> paccoin.conf
echo "server=1" >> paccoin.conf
echo "daemon=1" >> paccoin.conf
echo "listen=1" >> paccoin.conf
echo "staking=0" >> paccoin.conf
echo "masternode=1" >> paccoin.conf
echo "masternodeaddr=$ipaddr:7112" >> paccoin.conf
echo "masternodeprivkey=$mnkey" >> paccoin.conf


echo "###############################"
echo "#      Running the wallet     #"		
echo "###############################"
echo ""
cd ~/

./paccoind
sleep 60

syncedinfo=$( ./paccoin-cli mnsync status )
assetid=$( echo $syncedinfo | jq '.AssetID' )

if [ $assetid == 'null' ]; then
	echo "Wallet is not running or there is an issue, please restart wallet!"
	exit
fi

echo "###############################"
echo "#     Running the sentinel    #"		
echo "###############################"
echo ""
git clone "https://github.com/PACCommunity/sentinel"
cd sentinel
virtualenv ./venv
./venv/bin/pip install -r requirements.txt
venv/bin/python bin/sentinel.py
crontab 'crontab.txt'

cd ~/
./paccoin-cli getinfo

echo "Your masternode server is ready!"
echo "Don't forget to run the masternode from your cold wallet!"