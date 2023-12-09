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

add_executable(VisualDemoNormal
        "Demo/demoNormal.cpp")

add_executable(VisualDemoQuadtree
        "Demo/demoQuadtree.cpp")

target_include_directories(QuadtreeLib PRIVATE
        "includes/Quadtree")

target_include_directories(TestSuite PRIVATE
        "includes/Quadtree"
        "includes/catch2")

target_include_directories(VisualDemoNormal PRIVATE
        "includes/Visual/"
        "includes/Quadtree/")

target_include_directories(VisualDemoQuadtree PRIVATE
        "includes/Visual/"
        "includes/Quadtree/")

target_link_libraries(TestSuite PRIVATE QuadtreeLib)
target_link_libraries(VisualDemoNormal sfml-graphics QuadtreeLib)
target_link_libraries(VisualDemoQuadtree sfml-graphics QuadtreeLib)


