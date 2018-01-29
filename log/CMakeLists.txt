cmake_minimum_required(VERSION 3.9)
project(log VERSION 0.0.1 DESCRIPTION "log for esb project")

set(CMAKE_CXX_STANDARD 14)

include_directories($ENV{BOOST})
include_directories($ENV{SPDLOG})

link_directories($ENV{BOOST}/stage/lib)

add_library(log STATIC log.cpp)