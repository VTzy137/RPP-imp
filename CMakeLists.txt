cmake_minimum_required(VERSION 3.14)
project(RPP-imp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Export compile commands for IDE integration and development tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
# add_compile_options(-mfpath=sse -ffast-math)

file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS "library/**/*.cpp")


find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenCV REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)

include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}  # ✅ Add this
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
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${OpenCV_LIBS}  # ✅ Add this
)
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
