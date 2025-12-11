cmake_minimum_required(VERSION 3.10)
project(SmartHomeFinal)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# collect source files
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(smarthome ${SOURCES})

# install headers (optional)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION include)

# Added recommended compiler warning flags
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# To enable clang-tidy, set CMAKE_CXX_CLANG_TIDY: e.g.
# cmake -DCMAKE_CXX_CLANG_TIDY=clang-tidy ..
