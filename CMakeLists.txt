cmake_minimum_required(VERSION 3.16)
project(FinMLCpp VERSION 1.0 LANGUAGES CXX)

# C++ version
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include paths
include_directories(
    ${CMAKE_SOURCE_DIR}/include/FinancialDataStructures/BarAggregator/Policies
    ${CMAKE_SOURCE_DIR}/include/FinancialDataStructures/BarAggregator
    ${CMAKE_SOURCE_DIR}/include/FinancialDataStructures
    ${CMAKE_SOURCE_DIR}/include
)

# Just build the library from headers (no .cpp needed)
add_library(finml INTERFACE)
target_include_directories(finml INTERFACE ${CMAKE_SOURCE_DIR}/include)

# Build main separately
add_executable(main_exe src/main.cpp)
target_link_libraries(main_exe finml)

# Add tests
add_subdirectory(tests)