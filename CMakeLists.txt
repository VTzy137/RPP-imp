cmake_minimum_required(VERSION 3.14)
project(RPP-imp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS "library/**/*.cpp")

find_package(OpenCV REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

add_definitions(-DASSET_PATH=\"${CMAKE_SOURCE_DIR}/assets\")

add_library(rpp_lib STATIC ${LIB_SOURCES})
 
target_include_directories(rpp_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

set(APP_SOURCES
    src/main.cpp
    src/app.cpp
)

add_executable(RPP-imp ${APP_SOURCES})
target_link_libraries(RPP-imp PRIVATE 
    rpp_lib
    ${OpenCV_LIBS}
)
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
