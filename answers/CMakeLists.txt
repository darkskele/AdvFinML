# Collect all standalone analysis scripts in answers/
file(GLOB_RECURSE ANSWER_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Create a separate executable for each answer file (e.g., 2_1_b -> bin: answer_2_1_b)
foreach(source_file ${ANSWER_SOURCES})
    get_filename_component(filename ${source_file} NAME_WE)
    set(target_name answer_${filename})

    add_executable(${target_name} ${source_file})

    # Link to your main library (which already includes SQLite3, etc.)
    target_link_libraries(${target_name}
        PRIVATE
            finml
    )

    # Optional: give it access to your public headers
    target_include_directories(${target_name} PRIVATE
        ${CMAKE_SOURCE_DIR}/include
    )
endforeach()
