#!/bin/bash

mkdir -p build
cd build && cmake ../src -DCMAKE_CXX_FLAGS="-std=c++20 -O3" && make
