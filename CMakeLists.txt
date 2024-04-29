cmake_minimum_required(VERSION 3.24)
project(Pong)

set(CMAKE_CXX_STANDARD 14)
set(ICONS "assets/image")

add_executable(${PROJECT_NAME}
    ${ICONS}/pong.rc
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

link_directories(${CMAKE_SOURCE_DIR}/lib)