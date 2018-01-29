cmake_minimum_required(VERSION 3.9)
project(http VERSION 0.0.1 DESCRIPTION "http listener for esb project")

set(CMAKE_CXX_STANDARD 14)

include_directories($ENV{BOOST})
include_directories($ENV{SPDLOG})
include_directories(${esb_SOURCE_DIR}/log)
include_directories(${esb_SOURCE_DIR}/listener)

link_directories($ENV{BOOST}/stage/lib)

file(GLOB src "*.h" "*.cpp")

add_library(http SHARED ${src})