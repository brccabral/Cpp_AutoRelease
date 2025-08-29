cmake_minimum_required(VERSION 3.20)
project(AutoRelease)

include(GNUInstallDirs)

add_subdirectory(autorelease)

if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()
