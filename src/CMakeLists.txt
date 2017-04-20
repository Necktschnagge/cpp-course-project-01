cmake_minimum_required(VERSION 3.6)
project(HelloWorld)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
		GCC-make/main.cpp
		solution/solution.cpp solution/solution.h)
add_executable(Project1 ${SOURCE_FILES})