cmake_minimum_required(VERSION 3.24)
project(Quadtree)

set(CMAKE_CXX_STANDARD 17)

add_library(QuadtreeLib STATIC
        "src/AxisAlignedBoundingBox.cpp")

add_executable(Quadtree src/main.cpp)

target_include_directories(QuadtreeLib PRIVATE "includes/")