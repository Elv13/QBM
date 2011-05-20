#!/bin/dash
#EVENT=`dmesg | grep "7-2:1.0" | cut -f 10 -d/ | grep -e "[0-9]" -o`
sleep 3
X &
PID=$!
{
while [ "`pidof X`" != "" ]; do
  DISPLAY=:0 awesome 2> /dev/null
  if [ $? -eq 0 ]; then
    break
  fi
  sleep 0.05
done
} &
#sleep 3
#sudo rc prepost
#sudo rc post &

wait $PID
