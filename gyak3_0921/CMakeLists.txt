cmake_minimum_required(VERSION 3.31)
project(adatszerk_L03)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")

include_directories("../")

add_executable(L03_FixedIntStack FixedIntStackMain.cpp FixedIntStack.hpp)
add_executable(L03_DynamicIntStack DynamicIntStackMain.cpp DynamicIntStack.hpp)

add_executable(L03_FixedStack FixedStackMain.cpp FixedStack.hpp)
add_executable(L03_DynamicStack DynamicStackMain.cpp DynamicStack.hpp)

set_target_properties(L03_FixedIntStack PROPERTIES OUTPUT_NAME "L03_FixedIntStack.out")
set_target_properties(L03_DynamicIntStack PROPERTIES OUTPUT_NAME "L03_DynamicIntStack.out")

set_target_properties(L03_FixedStack PROPERTIES OUTPUT_NAME "L03_FixedStack.out")
set_target_properties(L03_DynamicStack PROPERTIES OUTPUT_NAME "L03_DynamicStack.out")

