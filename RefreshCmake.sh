#!/usr/bin/env sh

# expects to be run from the root folder of the project
mkdir -p build
cd build
cmake .. -G "Xcode" -DWITH_SDL2APPLICATION=ON #-DCORRADE_TESTSUITE_TARGET_XCTEST=ON
cd ..
