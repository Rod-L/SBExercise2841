cmake_minimum_required(VERSION 3.22)
project(SBExercise2841)

set(CMAKE_CXX_STANDARD 14)

add_executable(SBExercise2841 src/main.cpp include/Swimmer.h src/Swimmer.cpp include/SwimmingContest.h src/SwimmingContest.cpp)

target_include_directories(SBExercise2841 PUBLIC include)
