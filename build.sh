#!/bin/sh
rm -rf ./CMakeCache.txt ./CMakeFiles/ ./build
cmake -B ./build -DCMAKE_BUILD_TYPE=RelWithDebInfo && cmake --build ./build -v --config RelWithDebInfo
