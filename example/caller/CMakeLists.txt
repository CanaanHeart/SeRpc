cmake_minimum_required(VERSION 3.20)
project(CALLER)

add_executable(call_user_service ${PROJECT_SOURCE_DIR}/call_user_service.cpp)

target_link_libraries(call_user_service user_rpc saier_rpc protobuf zookeeper_mt)