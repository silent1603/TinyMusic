#!/bin/sh
if [ ! -d "./build" ]; then
    mkdir build
fi

git submodule update --init --recursive --remote

if [ ! -e "./vcpkg/vcpkg" ]; then
    echo isntall vcpkg
    ./vcpkg/bootstrap-vcpkg.sh
fi

cd build 
cmake .. 
make
cd ..
