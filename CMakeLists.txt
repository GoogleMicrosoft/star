cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(StarProject)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 查找当前目录及其子目录下的所有 .h 和 .cc 文件
file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")

# 将所有源文件和头文件添加到项目中
add_executable(StarExecutable ${SOURCE_FILES} ${HEADER_FILES})

include_directories(./)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/bazel-star/external/gtest/googletest/include)

# 如果需要链接其他库，可以在这里添加
# target_link_libraries(StarExecutable <library_name>)
