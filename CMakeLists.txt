cmake_minimum_required(VERSION 3.24)
project(Quadtree)

set(CMAKE_CXX_STANDARD 17)

add_library(QuadtreeLib STATIC
        "src/AxisAlignedBoundingBox.cpp"
        "src/Point.cpp")

add_library(TestSuite STATIC
        "test/main.cpp")

target_include_directories(QuadtreeLib PRIVATE
        "includes/Quadtree")

target_include_directories(TestSuite PRIVATE
        "includes/Quadtree"
        "includes/catch2")
