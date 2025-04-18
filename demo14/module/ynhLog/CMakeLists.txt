cmake_minimum_required(VERSION 3.0.0)
project(ynhLog)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(APPNAME ynhLog)
set(YNHLOG_VERSION_MAJOR 1)
set(YNHLOG_VERSION_MINOR 0)
set(YNHLOG_VERSION_PATCH 0)
set(YNHLOG_VERSION "${YNHLOG_VERSION_MAJOR}.${YNHLOG_VERSION_MINOR}.${YNHLOG_VERSION_PATCH}")
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
else()
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()
file(GLOB_RECURSE SOURCES_FILES 
${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
message("SOURCES_FILES:" ${SOURCES_FILES})
file(GLOB_RECURSE HEAD_FILES 
${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)
set(HEADER_DIRS "")
foreach(HEADER_FILE ${HEAD_FILES})
    get_filename_component(HEADER_DIR ${HEADER_FILE} DIRECTORY)
    list(APPEND HEADER_DIRS ${HEADER_DIR})
endforeach()
list(REMOVE_DUPLICATES HEADER_DIRS)
message("HEADER_DIRS:" ${HEADER_DIRS})
add_library(${APPNAME} SHARED ${SOURCES_FILES})
target_include_directories(${APPNAME} PRIVATE ${HEADER_DIRS})
set_target_properties(${APPNAME} PROPERTIES
VERSION ${YNHLOG_VERSION}
SOVERSION ${YNHLOG_VERSION_MAJOR})
set(INSTALL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/install)
install(TARGETS ${APPNAME}
    LIBRARY DESTINATION ${INSTALL_PATH}/lib
    ARCHIVE DESTINATION ${INSTALL_PATH}/lib
    RUNTIME DESTINATION ${INSTALL_PATH}/bin
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${INSTALL_PATH}/include)