cmake_minimum_required(VERSION 3.20)
project(DNS_LIB)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)

set(LIBRARY_OUTPUT_PATH ${LIBPATH})

add_library(dns_resolver SHARED ${SRC})

target_link_libraries(dns_resolver PUBLIC logger)