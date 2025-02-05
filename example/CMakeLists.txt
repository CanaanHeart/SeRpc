cmake_minimum_required(VERSION 3.20)
project(EXAMPLE)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
include_directories(${HEADPATH})

set(LIBRARY_OUTPUT_PATH ${LIBPATH})

add_library(user_rpc SHARED ${SRC})

add_subdirectory(${PROJECT_SOURCE_DIR}/callee)
add_subdirectory(${PROJECT_SOURCE_DIR}/caller)