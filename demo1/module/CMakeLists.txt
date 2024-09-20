cmake_minimum_required(VERSION 3.0)
project(test)
# 定义变量
# 静态库生成的路径
# 头文件目录
set(HEAD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/logger/)
# 静态库的名字
set(LOGGER_LIB_STATIC logger_lib_static)
# 动态库
set(LOGGER_LIB_SHARED logger_lib)

# 可执行程序的名字
set(APP app_demo)

# 添加子目录
add_subdirectory(logger)
add_subdirectory(src)