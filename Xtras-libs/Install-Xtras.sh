#!/bin/sh

# Tiny3D

## Unpack the source code.
unzip -o Tiny3D.zip

## Create the build directory.
cd Tiny3D

## Compile and install.
make && cd ../

# ps3soundlib

## Unpack the source code.
unzip -o ps3soundlib.zip &&

## Create the build directory.
cd ps3soundlib/libs

## make
mkdir -p /usr/local/ps3dev/portlibs/ppu/modules
make && cd ../../
