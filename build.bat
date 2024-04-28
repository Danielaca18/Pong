@echo off
rmdir /S/Q build
mkdir build
cd build
cmake .. -G "Unix Makefiles"
cmake --build .