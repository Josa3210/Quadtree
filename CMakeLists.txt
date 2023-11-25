cmake_minimum_required(VERSION 3.24)
project(Quadtree)

set(CMAKE_CXX_STANDARD 17)

add_library(QuadtreeLib STATIC
        "src/axisAlignedBoundingBox.cpp"
        "src/point.cpp" includes/Quadtree/object.h src/object.cpp)

add_executable(TestSuite
        "test/main.cpp"
        "test/axisAlignedBoundingBoxTest.cpp"
        "test/quadTreeTest.cpp" test/unordered_set_extensionTest.cpp)

target_include_directories(QuadtreeLib PRIVATE
        "includes/Quadtree")

target_include_directories(TestSuite PRIVATE
        "includes/Quadtree"
        "includes/catch2")

target_link_libraries(TestSuite PRIVATE QuadtreeLib)
