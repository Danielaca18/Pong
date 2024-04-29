@echo off
rmdir /S/Q build
mkdir build

set type=%1

IF /i "%1"=="D" (
    cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake
    cmake --build build
) ELSE (
    cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
    cmake --build build --config Release
)

::cmake --preset=default
::cmake --build build