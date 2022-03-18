cmake_minimum_required(VERSION 3.21)
project(Raycaster)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "SDL2-2.0.20\\x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(Raycaster
        main.cpp
        Utils.cpp Utils.h Image.cpp Image.h Map.cpp Map.h Player.cpp Player.h Texture.cpp Texture.h Sprite.cpp Sprite.h Renderer.cpp Renderer.h)
target_link_libraries(Raycaster ${SDL2_LIBRARY})