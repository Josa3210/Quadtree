cmake_minimum_required(VERSION 3.24)
project(Quadtree)

set(CMAKE_CXX_STANDARD 17)

add_library(QuadtreeLib STATIC
        "src/AxisAlignedBoundingBox.cpp"
        "src/Point.cpp" src/QuadTree.cpp includes/Quadtree/QuadTree.h)

add_executable(TestSuite
        "test/main.cpp" test/AxisAlignedBoundingBoxTest.cpp test/QuadTree.cpp)

target_include_directories(QuadtreeLib PRIVATE
        "includes/Quadtree")

target_include_directories(TestSuite PRIVATE
        "includes/Quadtree"
        "includes/catch2")

target_link_libraries(TestSuite PRIVATE QuadtreeLib)
