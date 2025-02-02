cmake_minimum_required(VERSION 3.10)

# 项目名称
project(StarProject)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置源文件目录
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# 查找所有的 .cc 和 .h 文件
file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cc" "${SOURCE_DIR}/*.h")

# 添加可执行文件
add_executable(StarExecutable ${SOURCES})

# 包含头文件目录
target_include_directories(StarExecutable PRIVATE ${SOURCE_DIR})
