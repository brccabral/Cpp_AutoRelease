find_package(SDL2 REQUIRED)
add_executable(sdl2_example)
target_sources(sdl2_example PRIVATE main.cpp)
target_link_libraries(sdl2_example PRIVATE SDL2 SDL2_image autorelease::autorelease)
add_custom_command(TARGET sdl2_example PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources
                   ${CMAKE_CURRENT_BINARY_DIR}/resources
)
