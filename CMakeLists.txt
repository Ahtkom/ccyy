cmake_minimum_required(VERSION 3.0.0)
project(ccyy VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(d:/pmk/project/ccyy/include)
aux_source_directory(d:/pmk/project/ccyy/src/math/algorithm/heuristic ALL_SRCS)

add_executable(ccyy main.cpp ${ALL_SRCS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
