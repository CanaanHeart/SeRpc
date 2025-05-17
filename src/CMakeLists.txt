cmake_minimum_required(VERSION 3.20)
project(SAIER_RPC)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
include_directories(${HEADPATH})

set(LIBRARY_OUTPUT_PATH ${LIBPATH})

add_library(saier_rpc SHARED ${SRC})

target_link_libraries(saier_rpc logger load_config dns_resolver serv threadpool timestamp zookeeper_mt)