cmake_minimum_required(VERSION 3.9)
project(listener VERSION 0.0.1 DESCRIPTION "listener for esb project")

set(CMAKE_CXX_STANDARD 14)

include_directories($ENV{BOOST})
include_directories($ENV{SPDLOG})
include_directories(${esb_SOURCE_DIR}/log)

link_directories($ENV{BOOST}/stage/lib)

add_executable(listener main.cpp)
target_link_libraries(listener log)
