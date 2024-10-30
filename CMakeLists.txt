cmake_minimum_required(VERSION 3.28)
project(test)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(my/thirdparty)
include_directories(${nlohmann_json_INCLUDE_DIRS})

add_executable(d01 optree.cc)
add_executable(d02 my/best.cc)
add_executable(d03 skip.cc)
add_executable(d04 kmp.cc)
add_executable(d05 sort.cc)
add_executable(d06 reasoning.cc)
add_executable(d07 combine.cc)
add_executable(d08 my/cnsearch.cc)
add_executable(d09 search.cc)
add_executable(d10 tire.cc)
add_executable(d11 multiply.cc)

target_link_libraries(d08 nlohmann_json::nlohmann_json)