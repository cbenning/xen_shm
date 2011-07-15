#!/bin/sh
rmmod xenshm
insmod xenshm.ko  || exit 1

# remove stale nodes
rm -f /dev/xenshm}

major=$(awk '/xenshm/ {print $1}' /proc/devices | head -1)

echo $major

mknod /dev/xenshm c $major 0
