cmake_minimum_required(VERSION 3.21)
project(autorelease VERSION 0.0.1)

add_library(autorelease INTERFACE)
add_library(autorelease::autorelease ALIAS autorelease)
target_compile_features(autorelease INTERFACE cxx_std_20)
target_sources(autorelease
               PUBLIC
               FILE_SET autorelease_headers
               TYPE HEADERS
               BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
               FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/autorelease/AutoRelease.hpp
)

install(TARGETS autorelease
        EXPORT autoreleaseTargets
        FILE_SET autorelease_headers DESTINATION ${CMAKE_INCLUDE_PATH}
)
install(EXPORT autoreleaseTargets
        FILE autoreleaseTargets.cmake
        NAMESPACE autorelease::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/autorelease
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/autoreleaseConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)
configure_file("${PROJECT_SOURCE_DIR}/../cmake/autoreleaseConfig.cmake.in" autoreleaseConfig.cmake @ONLY)
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/autoreleaseConfigVersion.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/autoreleaseConfig.cmake"
        DESTINATION lib/cmake/autorelease
)
