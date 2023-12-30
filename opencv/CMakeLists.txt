cmake_minimum_required(VERSION 3.0)

project(Test1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "> version: ${OpenCV_VERSION}")
message(STATUS "> libraries: ${OpenCV_LIBS}")
message(STATUS "> include: ${OpenCV_INCLUDE_DIRS}")

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/inc)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)

add_executable(main ${PROJECT_SOURCE_DIR}/main.cpp ${SRC_LIST})
target_link_libraries(main ${OpenCV_LIBS})
