#!/bin/sh
make menuconfig
make
make vmlinuz
make modules_install
cp -a arch/x86/boot/vmlinuz /boot/vmlinuz-2.6.29.2-xen-shm
mkinitramfs -o /boot/initrd.img-2.6.29.2-xen-shm 2.6.29.2