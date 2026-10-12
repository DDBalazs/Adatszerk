cmake_minimum_required(VERSION 3.31)
project(adatszerk_L06)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")

include_directories("../" "./")

add_executable(L06_AvlTree AvlTree/AvlTreeMain.cpp AvlTree/AvlTree.hpp AvlTree/AvlTreeExceptions.hpp)

set_target_properties(L06_AvlTree PROPERTIES OUTPUT_NAME "L06_AvlTree.out")
