set -e
      
echo "        ..........    												 "                                                  
echo "      .............. 												     "                                                
echo "   ....................   											 "                                            
echo "  .....-yyyyyyys+-:oo-..       oooooooo.      ooooo         oooooooo   " 
echo " ......:MMMMNNdddmMMMd...     MMMMNMMMMMh.   MMMMMMM      MMMMMMMMMM   "
echo "......:MMmy..-+MNdh:.....     MMMM: .dMMMy  oMMMyMMNN   .NMMMMy        "
echo "......:ddmm...-hdNm......     MMMM+-+mMMMs :MMMs dMMm   yMMMMo         "
echo "....:ohNMMNdoydNMMN/.....     MMMMMMMMMmo. NMMN  -MMMd  yMMMM.         "
echo "...+dMNdddNmmdhy+-.......     MMMM+::-    dMMMNmmmMMMMs :MMMMm.        "
echo "......::MMMm.............     MMMM:      yMMMdoooooNMMM  mMMMMNdddN+   "
echo " ......:MNdo.............     dddd-     ddddd.     ddddd.  :ohdmmdhy:  "
echo "  ....-+-..............                                                "
echo "    .................                                                  "
echo "       ...........  													 "

echo "################################################"
echo "#         Welcome PAC wallet update		     #"		
echo "################################################"
echo "" 
echo "This script will update PAC to the latest version (xxx)"
echo "Before running the script we recommend to backup your private keys and your wallet.dat file that is under ./paccoincore/wallet.dat even though this script will not affect them"
read -p "Do you want to autobackup wallet.dat and continue with the process? [y/n]:" cont
if [ $cont = 'n' ] || [ $cont = 'no' ] || [ $cont = 'N' ] || [ $cont = 'No' ]; then
	exit
fi

currpath=$( pwd )
echo "Backing up the wallet.dat into $currpath"
cp .paccoincore/wallet.dat "$currpath/walletbackup.dat"
echo "Wallet.dat backup is on: $currpath"

if [ -e ~/paccoin-cli ] && [ -e ~/paccoind ]; then
	echo ""
	echo "#######################################"
	echo "#   Stopping pac services (daemon)    #"		
	echo "#######################################"
	echo ""

	wallstatus=$( ./paccoin-cli mnsync status ) || true
	if [ -z "$wallstatus" ]; then
		echo "Daemon is not running no need to stop it"
	else
		echo "Stopping the Daemon"
		./paccoin-cli stop
		sleep 60
		
		wallstatus=$( ./paccoin-cli mnsync status ) || true
		if [ -z "$wallstatus" ]; then
			echo "Daemon stopped!"
		else
			echo "Daemon can not be stopped! Please kill the deamon process or run ./pacoin-cli stop, then run the script again"
			exit
		fi
	fi

	echo ""
	echo "###############################"
	echo "#   Removing old binaries    #"		
	echo "###############################"
	echo ""

	echo "Removing paccoin-cli"
	rm paccoin-cli

	echo "Removing paccoind"
	rm paccoind

	if [ -e ~/paccoin-qt ]; then
		echo "Removing paccoin-qt"
		rm paccoin-qt
	fi

	if [ -e ~/PAC-v0.12.2.3-ubuntu-16.04-x64.tar.gz ]; then
		echo "Removing PAC-v0.12.2.3-ubuntu-16.04-x64.tar.gz"
		rm PAC-v0.12.2.3-ubuntu-16.04-x64.tar.gz
	fi

	if [ -d ~/PAC-v0.12.2.3-ubuntu-16.04-x64 ]; then
		echo "Removing PAC-v0.12.2.3-ubuntu-16.04-x64 directory"
		rm -r PAC-v0.12.2.3-ubuntu-16.04-x64
	fi
 
else
	echo "No PAC binaries found, will install/setup new binaries instead"
	echo "If you already have binaries please make sure you are running this script on the path on which your binaries got stored"
fi

echo ""
echo "###############################"
echo "#   Get/Setup new binaries    #"		
echo "###############################"
echo ""
wget "https://github.com/PACCommunity/PAC/releases/download/v0.12.2.3/PAC-v0.12.2.3-ubuntu-16.04-x64.tar.gz"
tar xvf 'PAC-v0.12.2.3-ubuntu-16.04-x64.tar.gz'
sudo rm PAC-v0.12.2.3-ubuntu-16.04-x64.tar.gz
currpath=$( pwd )
echo "Binaries got stored on: $currpath"
chmod +x paccoind
chmod +x paccoin-cli

echo ""
echo "##################################################################"
echo "#   Updating the sentinel (Will be applied only on masternodes)       #"		
echo "##################################################################"
echo ""

if [ -d ~/sentinel ]; then
	cd sentinel
	git pull
	cd ..
else
	echo "No sentinel was found, in case this node is a masternode follow the instructions below if not sure just IGNORE this message!"
	echo "Intructions:"
	echo "1) Go to the sentinel folder"
	echo "2) Run this command: sudo git pull"
fi

echo ""
echo "###########################"
echo "#   Running the daemon    #"		
echo "###########################"
echo ""

./paccoind -daemon=1
echo "Waiting for daemon to be up and running"
sleep 10
echo "PAC Updated!"