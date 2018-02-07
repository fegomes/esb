cmake_minimum_required(VERSION 3.9)
project(shared VERSION 0.0.1 DESCRIPTION "shared memory for esb project")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${esb_SOURCE_DIR}/bin)

include_directories($ENV{BOOST})
include_directories($ENV{SPDLOG})
include_directories(${esb_SOURCE_DIR}/log)
include_directories(${esb_SOURCE_DIR}/listener)

link_directories($ENV{BOOST}/stage/lib)

file(GLOB src "*.h" "*.cpp")

add_library(shared SHARED ${src})