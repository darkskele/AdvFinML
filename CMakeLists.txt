cmake_minimum_required(VERSION 3.16)
project(FinML VERSION 1.0 LANGUAGES CXX)

# Set global standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(tests)
add_subdirectory(answers)
