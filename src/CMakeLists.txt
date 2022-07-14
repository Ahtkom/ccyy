aux_source_directory(${PROJECT_SOURCE_DIR}/src/math/algorithm SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/math/algorithm/heursitic SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/util SRCS)

add_executable(ccyy ${PROJECT_SOURCE_DIR}/main.cpp ${SRCS})

# add_library(ccyy SHARED ${SRCS})
# set(CMAKE_CXX_FLAGS_DEBUG "-O3")