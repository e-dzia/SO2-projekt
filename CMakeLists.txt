cmake_minimum_required(VERSION 3.7)
project(bakery)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-pthread")

set(SOURCE_FILES bakery.cpp Baker.cpp Baker.h Oven.cpp Oven.h Client.cpp Client.h Utility.cpp Utility.h Shelf.cpp Shelf.h Account.cpp Account.h)
add_executable(so2 ${SOURCE_FILES})