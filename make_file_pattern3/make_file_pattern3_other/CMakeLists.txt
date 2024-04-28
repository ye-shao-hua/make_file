cmake_minimum_required(VERSION 3.11)
project(txtreader)

set(CMAKE_CXX_STANDARD 23)

include_directories(./include)
#include_directories(./etc/fe_tools/include)
#include_directories(./../include/vec)
#include_directories(./../include/point)
#include_directories(./../include/cell)

add_executable(txtreader txtread.cpp)
target_link_libraries(txtreader boost_program_options)
