cmake_minimum_required(VERSION 3.20)
project(SERV_LIB)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
include_directories(${HEADPATH})

set(LIBRARY_OUTPUT_PATH ${LIBPATH})

add_library(serv SHARED ${SRC})

target_link_libraries(serv PUBLIC logger dns_resolver threadpool timestamp pthread)
