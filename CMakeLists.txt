set(TARGET "sokoban")

cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(${TARGET})

# add shared libraries here
add_subdirectory(catch)
add_subdirectory(sokobanlib)
add_subdirectory(sokoban)
