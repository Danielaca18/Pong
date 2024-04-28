@echo off
rmdir /S/Q build
mkdir build

cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build

::cmake --preset=default
::cmake --build build