cmake_minimum_required(VERSION 3.16)
project(ASD2022-L1-Complexite)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wsign-conversion -pedantic")

add_executable(L1-example example.cpp)

add_executable(L1-mainTestCustomSorts mainTestCustomSorts.cpp)

add_executable(L1-mainTimeMeasurement mainTimeMeasurement.cpp)

add_executable(L1-mainCountComparisonAndAffectation mainCountComparisonAndAffectation.cpp)