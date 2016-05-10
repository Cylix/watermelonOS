#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/WatermelonOS.kernel isodir/boot/WatermelonOS.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "WatermelonOS" {
	multiboot /boot/WatermelonOS.kernel
}
EOF
grub-mkrescue -o $ISO isodir
