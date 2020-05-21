cmake_minimum_required(VERSION 3.15)
project(clion)

set(CMAKE_CXX_STANDARD 11)
include_directories(./include)
include_directories("${PROJECT_SOURCE_DIR}add") #添加头文件

add_subdirectory(include)                # 添加 add子目录
aux_source_directory(. DIR_SRCS)
add_executable(clion ${DIR_SRCS})  #制定生成目标
target_link_libraries(clion Config)  #添加链接库

