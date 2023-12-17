cmake_minimum_required(VERSION 3.22)
project(TetrisIm)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(tetris_im ${SOURCES})

target_link_libraries(tetris_im
        raylib
        GL
        m
        pthread
        dl
        rt
        X11
)

target_compile_options(tetris_im PRIVATE
        -Wall
        -Wno-missing-braces
        -s
        -O1
        -D_DEFAULT_SOURCE
        -DPLATFORM_DESKTOP
)