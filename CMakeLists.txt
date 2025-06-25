cmake_minimum_required(VERSION 3.16)
project(FinMLCpp VERSION 1.0 LANGUAGES CXX)

# C++ version
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project structure
include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Library
add_library(finml STATIC ${SRC_FILES})

# Main executable
add_executable(main_exe ${SRC_FILES})
target_link_libraries(main_exe finml)
