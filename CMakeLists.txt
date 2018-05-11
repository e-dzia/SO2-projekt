cmake_minimum_required(VERSION 3.7)
project(bakery)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-pthread")

set(SOURCE_FILES main.cpp Baker.cpp Baker.h Oven.cpp Oven.h Client.cpp Client.h)
add_executable(so2 ${SOURCE_FILES})