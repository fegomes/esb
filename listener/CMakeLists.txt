cmake_minimum_required(VERSION 3.9)
project(listener VERSION 0.0.1 DESCRIPTION "listener for esb project")

set(CMAKE_CXX_STANDARD 14)

if(UNIX)
  find_package(Threads REQUIRED)
endif(UNIX)

include_directories($ENV{BOOST})
include_directories($ENV{SPDLOG})
include_directories(${esb_SOURCE_DIR}/log)

link_directories($ENV{BOOST}/stage/lib)

add_executable(listener main.cpp)

if(UNIX)
target_link_libraries(listener log ${CMAKE_THREAD_LIBS_INIT} boost_system boost_filesystem dl)
else()
target_link_libraries(listener log)
endif(UNIX)
