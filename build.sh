#!/bin/sh
CMAKE_BUILD_TYPE=RelWithDebInfo
rm -rf ./CMakeCache.txt ./CMakeFiles/ ./build
cmake -B ./build -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} && cmake --build ./build -v --config ${CMAKE_BUILD_TYPE}
