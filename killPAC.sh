#!/bin/bash
PID=`ps -eaf | grep Paccoin-Qt | grep -v grep | awk '{print $2}'`
if [[ "" !=  "$PID" ]]; then
  echo "killing $PID"
  kill -9 $PID
else
  echo "No Paccoin-Qt process running. QT will not kill any process" false
fi

