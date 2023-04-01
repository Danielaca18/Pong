cmake_minimum_required(VERSION 3.24)
project(C___Pong)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "SDL2-2.26.4\\x86_64-w64-mingw32")
set(SDL2_TTF_PATH "SDL2_ttf-2.20.2\\x86_64-w64-mingw32")
set(SDL2_IMAGE_PATH "SDL2_image-2.6.3\\x86_64-w64-mingw32")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR})

add_executable(Pong
    GameController.cpp
    GameController.h
    GameState.h
    GameView.cpp
    GameView.h
    main.cpp)

target_link_libraries(Pong
        ${SDL2_LIBRARY}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES})

if (WIN32)
file(COPY ${CMAKE_SOURCE_DIR}/SDL2-2.26.4/x86_64-w64-mingw32/bin/SDL2.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/)
file(COPY ${CMAKE_SOURCE_DIR}/SDL2_ttf-2.20.2/x86_64-w64-mingw32/bin/SDL2_ttf.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/)
file(COPY ${CMAKE_SOURCE_DIR}/SDL2_image-2.6.3/x86_64-w64-mingw32/bin/SDL2_image.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
endif (WIN32)