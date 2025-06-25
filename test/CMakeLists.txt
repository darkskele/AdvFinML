cmake_minimum_required(VERSION 3.16)
project(FinMLTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find GTest
find_package(GTest REQUIRED)

# Project includes
include_directories(${CMAKE_SOURCE_DIR}/../include)

# Collect source files
file(GLOB_RECURSE TEST_SOURCES ${CMAKE_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE LIB_SOURCES ${CMAKE_SOURCE_DIR}/../src/*.cpp)

# Main test executable
add_executable(finml_tests ${TEST_SOURCES} ${LIB_SOURCES})

target_link_libraries(finml_tests
  PRIVATE
    GTest::gtest_main
)

# Discover tests
include(GoogleTest)
gtest_discover_tests(finml_tests)
