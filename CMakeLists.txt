cmake_minimum_required(VERSION 3.0.0)
project(ccyy VERSION 0.1.0)


set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/Release)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/Debug)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)