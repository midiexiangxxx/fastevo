cmake_minimum_required(VERSION 3.16)

project(fevo)
set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAG} -E -P")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAG} -march=native -O3 -flto -fno-fat-lto-objects")

include(CheckIPOSupported)
check_ipo_supported(RESULT supported OUTPUT error)
if(supported)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
    message(WARNING "IPO is not supported: ${error}")
endif()

find_package(Eigen3 REQUIRED)

add_executable(${PROJECT_NAME} main.cpp include)
target_include_directories(${PROJECT_NAME} PRIVATE include ${EIGEN3_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE -lboost_program_options)
