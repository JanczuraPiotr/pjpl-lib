cmake_minimum_required(VERSION 3.10)

project(pjpl-lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wpedantic -Wextra -Werror -Wconversion -pedantic-errors -Weffc++ -MMD -MP -MF")

include_directories(lib)

add_subdirectory(test)