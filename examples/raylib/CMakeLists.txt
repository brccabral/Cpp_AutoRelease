find_package(raylib REQUIRED)
add_executable(raylib_example)
target_sources(raylib_example PRIVATE main.cpp)
target_link_libraries(raylib_example PRIVATE raylib autorelease)
add_custom_command(TARGET raylib_example PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources
                   ${CMAKE_CURRENT_BINARY_DIR}/resources
)
