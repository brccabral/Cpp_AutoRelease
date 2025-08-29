add_library(autorelease INTERFACE)
target_compile_features(autorelease INTERFACE cxx_std_20)
target_sources(autorelease
               PUBLIC
               FILE_SET autorelease_headers
               TYPE HEADERS
               BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
               FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/autorelease/AutoRelease.hpp
)

install(TARGETS autorelease
        EXPORT autorelease_targets
        FILE_SET autorelease_headers DESTINATION ${CMAKE_INCLUDE_PATH}
)
