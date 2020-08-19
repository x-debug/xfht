cmake_minimum_required(VERSION 3.5)
project(hashtable C)

include_directories(inc)

set(CMAKE_C_STANDARD 99)

add_executable(hashtable main.c src/hashtable.c src/prime.c)

target_link_libraries(hashtable -lm)