cmake_minimum_required(VERSION 3.28)
project(
    logfacade
    VERSION 0.0.0
    LANGUAGES CXX
)

add_library(
    logfacade
    INTERFACE
)

target_include_directories(logfacade INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Install the library
install(
    DIRECTORY include/
    DESTINATION include
)

# Export the library for use in other projects
install(
    TARGETS logfacade
    EXPORT logfacade
    INCLUDES DESTINATION include
)

install(
    EXPORT logfacade-targets
    FILE logfacade-config.cmake
    NAMESPACE logfacade::
    DESTINATION lib/cmake/logfacade
)