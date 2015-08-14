cmake_minimum_required(VERSION 2.8)

add_executable(ScheduledExecutor Starter.cpp)

SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -W1,-no-as-needed -Wall" )
