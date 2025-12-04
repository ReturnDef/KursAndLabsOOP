cmake_minimum_required(VERSION 3.10)
project(SmartHomeDemo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCES
    src/*.cpp
)

add_executable(smarthome ${SOURCES})

# For convenience, install header files into build/include (optional)
add_custom_target(copy_headers ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/include
)
