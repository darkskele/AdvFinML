# Grab all .cpp source files from src/
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Define the finml library
add_library(finml STATIC ${SOURCES})

# Expose all necessary include directories (flat include paths in headers)
target_include_directories(finml PUBLIC
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/include/FinancialDataStructures
  ${CMAKE_SOURCE_DIR}/include/FinancialDataStructures/BarAggregator
  ${CMAKE_SOURCE_DIR}/include/FinancialDataStructures/BarAggregator/Policies
  ${CMAKE_SOURCE_DIR}/include/Streaming
  ${CMAKE_SOURCE_DIR}/include/Streaming/Sources
)

# SQL
find_package(SQLite3 REQUIRED)

# Link SQLite3 into the finml target
target_link_libraries(finml
  PRIVATE
    SQLite::SQLite3  
)
