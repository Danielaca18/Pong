cmake_minimum_required(VERSION 3.24)
project(C___Pong)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
#set(SDL2_PATH "SDL2-2.26.4\\x86_64-w64-mingw32")
#set(SDL2_TTF_PATH "SDL2_ttf-2.20.2\\x86_64-w64-mingw32")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(${PROJECT_NAME}
    src/GameController.cpp
    src/GameController.h
    src/GameState.h
    src/GameView.cpp
    src/GameView.h
    src/font.cpp
    src/font.h
    src/main.cpp)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)

find_package(SDL2_ttf CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_ttf::SDL2_ttf)


#include_directories(${SDL2_INCLUDE_DIR}
#                    ${SDL2_TTF_INCLUDE_DIR})
link_directories(${CMAKE_SOURCE_DIR}/lib)

#target_link_libraries(C___Pong
#        ${SDL2_LIBRARY}
#        ${SDL2_TTF_LIBRARIES})

if (WIN32)
file(COPY ${CMAKE_SOURCE_DIR}/SDL2-2.26.4/x86_64-w64-mingw32/bin/SDL2.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/)
file(COPY ${CMAKE_SOURCE_DIR}/SDL2_ttf-2.20.2/x86_64-w64-mingw32/bin/SDL2_ttf.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/)
file(COPY resources/font DESTINATION ${CMAKE_BINARY_DIR})
endif (WIN32)