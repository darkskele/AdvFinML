# Create a test project
project(FinMLTests LANGUAGES CXX)

# Use modern C++
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GoogleTest must be available
find_package(GTest REQUIRED)

# Grab all test source files
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Build the test executable
add_executable(finml_tests ${TEST_SOURCES})

# Include paths 
target_include_directories(finml_tests PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)

# Link against finml and GTest
target_link_libraries(finml_tests
  PRIVATE
    finml
    GTest::gtest_main
    pthread
)

# Auto-discover and register tests
include(GoogleTest)
gtest_discover_tests(finml_tests)
