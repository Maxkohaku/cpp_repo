cmake_minimum_required(VERSION 3.0.0)
project(app)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(APP_NAME test)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/output)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
    # set(CMAKE_BUILD_TYPE Release)
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Configuring for Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
else()
    message(STATUS "Configuring for Release")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()
file(GLOB_RECURSE SOURCES_FILES ${CMAKE_CURRENT_SOURCE_DIR}/module/**.cpp)
file(GLOB_RECURSE HEAD_FILES 
${CMAKE_CURRENT_SOURCE_DIR}/module/**.h
${CMAKE_CURRENT_SOURCE_DIR}/module/**.hpp)
set(HEADER_DIRS "")
foreach(HEADER_FILE ${HEAD_FILES})
    get_filename_component(HEADER_DIR ${HEADER_FILE} DIRECTORY)
    list(APPEND HEADER_DIRS ${HEADER_DIR})
endforeach()
list(REMOVE_DUPLICATES HEADER_DIRS)

message("SOURCES_FILES:" ${SOURCES_FILES})
message("HEADER_DIRS:" ${HEADER_DIRS})
# message("LIBS_DIRS:" ${LIBS_DIRS})

add_executable(${APP_NAME} ${SOURCES_FILES})
target_include_directories(${APP_NAME} PRIVATE ${HEADER_DIRS})
target_link_libraries(${APP_NAME} PRIVATE pthread)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${APP_NAME} PRIVATE DEBUG=false)
else()
    target_compile_definitions(${APP_NAME} PRIVATE DEBUG=true)
endif()