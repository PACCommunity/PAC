#!/bin/bash
# use testnet settings,  if you need mainnet,  use ~/.paccoincore/paccoind.pid file instead
paccoin_pid=$(<~/.paccoincore/testnet3/paccoind.pid)
sudo gdb -batch -ex "source debug.gdb" paccoind ${paccoin_pid}
