cmake_minimum_required(VERSION 3.14)
project(RPP-imp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(COPY assets/ DESTINATION assets)

# Include directories
include_directories(include include/function)

# Add the libraries
add_library(mutation library/function/mutation.cpp)
add_library(genetic library/function/genetic.cpp)

# Add executable
add_executable(RPP-imp src/main.cpp src/app.cpp)

# Link the libraries to the main program
target_link_libraries(RPP-imp PRIVATE mutation genetic)
