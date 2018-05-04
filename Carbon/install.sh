#!/usr/bin/env bash
ROOT=`pwd`
BUILD=Build/Build
MOUNT=/mnt/Carbon
GRUB=grub.img
TARGET=$ROOT/Carbon.img
test -d Build || mkdir Build
test -d $MOUNT || sudo mkdir -p $MOUNT
echo "Compiling source"
cd Build
cmake ../
make
echo "Generate image"
cd $ROOT
cp $GRUB $TARGET
sudo mount $TARGET $MOUNT
sudo cp $BUILD/kernel.elf $MOUNT/boot
sudo umount $MOUNT
echo "Done"
