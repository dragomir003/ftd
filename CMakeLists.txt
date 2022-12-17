cmake_minimum_required(VERSION 3.16)
project(ftd LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

enable_testing()

include_directories(include)

add_subdirectory(tests)
