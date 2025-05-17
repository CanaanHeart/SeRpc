cmake_minimum_required(VERSION 3.20)
project(SE_RPC)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall")

set(LIBPATH ${PROJECT_SOURCE_DIR}/lib)
set(HEADPATH ${PROJECT_SOURCE_DIR}/inc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(${HEADPATH})

add_subdirectory(${PROJECT_SOURCE_DIR}/logger)
add_subdirectory(${PROJECT_SOURCE_DIR}/load_config)
add_subdirectory(${PROJECT_SOURCE_DIR}/dns_resolver)
add_subdirectory(${PROJECT_SOURCE_DIR}/serv)
add_subdirectory(${PROJECT_SOURCE_DIR}/threadpool)
add_subdirectory(${PROJECT_SOURCE_DIR}/time)
add_subdirectory(${PROJECT_SOURCE_DIR}/example)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)

link_directories(${LIBPATH})
