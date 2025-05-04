cmake_minimum_required(VERSION 3.14)
project(RPP-imp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS "library/**/*.cpp")


find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(GLEW REQUIRED)

# Include dirs
include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
)

add_definitions(-DASSETS_PATH="${CMAKE_SOURCE_DIR}/assets")


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
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLFW_LIBRARIES}
)
