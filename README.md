# BATTLECITY 2018 #

## Prerequisites ##

CMake 3.10 or higher, SDL2 2.0.9 or higher, C++17 compliant compiler

## Building ##

### Windows ###

```cmd
mkdir build
cd build
cmake ..
```

then open the created Visual Studio solution

### MacOS ###
```sh
mkdir build
cd build
cmake .. -G "Xcode" -DWITH_SDL2APPLICATION=ON
```

then open the created XCode project
