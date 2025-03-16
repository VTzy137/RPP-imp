cmake_minimum_required(VERSION 3.14)
project(RPP-imp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Add executable
add_executable(RPP-imp src/main.cpp)
