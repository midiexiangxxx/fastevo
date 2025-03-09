cmake_minimum_required(VERSION 3.16)

project(fevo)
set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE -lboost_program_options)