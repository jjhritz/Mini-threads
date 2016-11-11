cmake_minimum_required(VERSION 2.6)
project(cse330project)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
#set(SOURCE_FILES proj-3.c q.h tcb.h threads.h sem.h)
set(SOURCE_FILES q.h tcb.h threads.h sem.h proj-4.c)

add_executable(cse330project ${SOURCE_FILES})
set_target_properties(cse330project PROPERTIES LINKER_LANGUAGE C)
