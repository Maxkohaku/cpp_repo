cmake_minimum_required(VERSION 3.10.0)
project(Demo)
set(APP_NAME demo)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_PREFIX_PATH "/home/ynh/git_ws/YnhCppRepo/YPackage")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/output)
file(GLOB_RECURSE SOURCES_FILES ${CMAKE_CURRENT_SOURCE_DIR}/module/**.cpp)

file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/module/**.h ${CMAKE_CURRENT_SOURCE_DIR}/module/**.hpp)
set(HEADER_DIRS "")
foreach(HEADER_FILE ${HEADER_FILES})
    get_filename_component(HEADER_DIR ${HEADER_FILE} DIRECTORY)
    list(APPEND HEADER_DIRS ${HEADER_DIR})
endforeach()
list(REMOVE_DUPLICATES HEADER_DIRS)
find_package(yLog REQUIRED)
message(STATUS "YLOG_INCLUDE_DIR ${YLOG_INCLUDE_DIR}")
add_executable(${APP_NAME} ${SOURCES_FILES})
target_include_directories(${APP_NAME} PRIVATE 
    ${HEADER_DIRS}
    ${YLOG_INCLUDE_DIR})
target_link_libraries(${APP_NAME} PRIVATE 
    pthread
    ${YLOG_LIBRARY})

message(STATUS "CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE}")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${APP_NAME} PRIVATE -g)
else()
    target_compile_options(${APP_NAME} PRIVATE -Og -g)
endif()