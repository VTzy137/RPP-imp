cmake_minimum_required(VERSION 3.14)
project(RPP-imp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Add the library
add_library(mutation library/function/mutation.cpp)
# Link the library to the main program
target_link_libraries(RPP-imp PRIVATE mutation)

# Add executable
add_executable(RPP-imp src/main.cpp)
