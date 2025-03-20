cmake_minimum_required(VERSION 3.16)

project(fevo)
set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAG} -E -P")

find_package(Eigen3 REQUIRED)

add_executable(${PROJECT_NAME} main.cpp include)
target_include_directories(${PROJECT_NAME} PRIVATE include ${EIGEN3_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE -lboost_program_options)
