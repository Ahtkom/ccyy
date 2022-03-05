cmake_minimum_required(VERSION 3.0.0)
project(ccyy VERSION 0.1.0)


set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/Release/linux)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/Debug/linux)

include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(${PROJECT_SOURCE_DIR}/src/math/algorithm/heuristic SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/math/algorithm SRCS)



# add_executable(ccyy main.cpp ${SRCS})
add_library(ccyy SHARED ${SRCS})