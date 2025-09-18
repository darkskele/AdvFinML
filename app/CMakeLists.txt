# Grab all .cpp files 
file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Create the executable for the app
add_executable(finml_app ${APP_SOURCES})

# Inherit public includes from the finml library
target_include_directories(finml_app PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)

# Link the main app to the library
target_link_libraries(finml_app
  PRIVATE
    finml
)
