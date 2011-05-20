#!/bin/dash

#
# Critical component to start X
# Be sure the hardware is ready before leaving this script
#
#

#Modprobe nouveay
modprobe nouveau &
MOD_PID=$!

/etc/init.d/readahead-list-early startc &
/etc/init.d/load start &
/etc/init.d/hostname start &
/etc/init.d/termencoding start &
/etc/init.d/readahead-list start &

#Wait for nouveau to finish
wait $MOD_PID
