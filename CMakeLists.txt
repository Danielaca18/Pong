cmake_minimum_required(VERSION 3.24)
project(C___Pong)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "SDL2-2.26.4\\x86_64-w64-mingw32")
set(SDL2_TTF_PATH "SDL2_ttf-2.20.2\\x86_64-w64-mingw32")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR})
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(C___Pong
    GameController.cpp
    GameController.h
    GameState.h
    GameView.cpp
    GameView.h
    main.cpp)

target_link_libraries(C___Pong
        ${SDL2_LIBRARY}
        ${SDL2_TTF_LIBRARIES})

file(COPY ${CMAKE_SOURCE_DIR}/SDL2-2.26.4/x86_64-w64-mingw32/bin/SDL2.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/)
file(COPY ${CMAKE_SOURCE_DIR}/SDL2_ttf-2.20.2/x86_64-w64-mingw32/bin/SDL2_ttf.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/)
file(COPY font DESTINATION ${CMAKE_BINARY_DIR})