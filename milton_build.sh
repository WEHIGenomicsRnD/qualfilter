#!/bin/bash

export LD_LIBRARY_PATH="/stornext/System/data/apps/gcc/gcc-12.2.0/lib64:/stornext/System/data/apps/gcc/gcc-12.2.0/lib"
export LIBRARY_PATH="/stornext/System/data/apps/gcc/gcc-12.2.0/lib64:/stornext/System/data/apps/gcc/gcc-12.2.0/lib"
export CPATH="/stornext/System/data/apps/gcc/gcc-12.2.0/include"

module load gcc/12.2.0 cmake

mkdir -p build
cd build && cmake ../src -DCMAKE_CXX_FLAGS="-std=c++20 -O3" && make
