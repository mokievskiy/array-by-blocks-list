cmake_minimum_required(VERSION 3.10)
project(List)

set(CMAKE_CXX_STANDARD 14)

enable_testing()

include_directories(List)

set(SOURCE_LIB main.cpp List/list.cpp)
add_executable(main ${SOURCE_LIB})
