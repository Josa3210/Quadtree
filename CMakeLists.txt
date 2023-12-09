cmake_minimum_required(VERSION 3.24)
project(Quadtree)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git)
FETCHCONTENT_MAKEAVAILABLE(SFML)


add_library(QuadtreeLib STATIC
        "src/quadtree/axisAlignedBoundingBox.cpp"
        "src/quadtree/point.cpp")

add_executable(TestSuite
        "test/main.cpp"
        "test/axisAlignedBoundingBoxTest.cpp"
        "test/quadTreeTest.cpp"
        "test/unordered_set_extensionTest.cpp")

add_executable(VisualDemo
        "Demo/demo.cpp")

target_include_directories(QuadtreeLib PRIVATE
        "includes/Quadtree")

target_include_directories(TestSuite PRIVATE
        "includes/Quadtree"
        "includes/catch2")

target_include_directories(VisualDemo PRIVATE
        "includes/Visual/"
        "includes/Quadtree/")

target_link_libraries(TestSuite PRIVATE QuadtreeLib)
target_link_libraries(VisualDemo sfml-graphics QuadtreeLib)


