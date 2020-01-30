cmake_minimum_required(VERSION 3.1)

project(get-or-return)

set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(TST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -Wall -O0 -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Os -pedantic")

enable_testing()
add_subdirectory(test)
