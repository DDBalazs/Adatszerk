cmake_minimum_required(VERSION 3.31)
project(adatszerk_L04)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")

include_directories("../" "./")

add_executable(L04_FixedQueue queue/FixedQueue.hpp queue/QueueExceptions.hpp queue/FixedQueueMain.cpp)
add_executable(L04_DynamicQueue queue/DynamicQueue.hpp queue/QueueExceptions.hpp queue/DynamicQueueMain.cpp)
add_executable(L04_LinkedList list/ListMain.cpp list/List.hpp list/ListException.hpp)

set_target_properties(L04_FixedQueue PROPERTIES OUTPUT_NAME "L04_FixedQueue.out")
set_target_properties(L04_DynamicQueue PROPERTIES OUTPUT_NAME "L04_DynamicQueue.out")
set_target_properties(L04_LinkedList PROPERTIES OUTPUT_NAME "L04_LinkedList.out")

