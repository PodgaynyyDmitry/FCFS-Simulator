cmake_minimum_required(VERSION 3.16)

project(FCFS_simulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(FCFS_simulator
  main.cpp
  process.h process.cpp
  scheduler.h scheduler.cpp
)
