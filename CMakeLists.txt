cmake_minimum_required(VERSION 2.8)
project(ini)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(./include)
include_directories("${PROJECT_SOURCE_DIR}") #添加头文件


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

add_subdirectory(include)                # 添加 add子目录
aux_source_directory(. DIR_SRCS)
add_executable(ini ${DIR_SRCS})  #制定生成目标
target_link_libraries(ini Config)  #添加链接库

