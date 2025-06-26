cmake_minimum_required(VERSION 3.16)
project(FinMLTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

file(GLOB_RECURSE TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(finml_tests ${TEST_SOURCES})

target_include_directories(finml_tests PRIVATE 
  ${CMAKE_SOURCE_DIR}/include/FinancialDataStructures/BarAggregator/Policies
  ${CMAKE_SOURCE_DIR}/include/FinancialDataStructures/BarAggregator
  ${CMAKE_SOURCE_DIR}/include/FinancialDataStructures
  ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(finml_tests
    PRIVATE
    finml
    GTest::gtest_main
    pthread
)

include(GoogleTest)
gtest_discover_tests(finml_tests)
