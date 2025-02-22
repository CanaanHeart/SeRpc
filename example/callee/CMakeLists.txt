cmake_minimum_required(VERSION 3.20)
project(CALLEE)

add_executable(user_service ${PROJECT_SOURCE_DIR}/user_service.cpp)

target_link_libraries(user_service user_rpc saier_rpc protobuf)