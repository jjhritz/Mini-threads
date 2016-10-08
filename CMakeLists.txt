cmake_minimum_required(VERSION 3.6)
project(cse330project)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES q.h tcb.h threads.h)
add_executable(cse330project ${SOURCE_FILES})