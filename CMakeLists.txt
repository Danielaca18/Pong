cmake_minimum_required(VERSION 3.24)
project(C___Pong)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "SDL2-2.26.4\\x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

include_directories(.)

add_executable(C___Pong
    GameController.cpp
    GameController.h
    GameState.h
    GameView.cpp
    GameView.h
    main.cpp)

target_link_libraries(C___Pong ${SDL2_LIBRARY})