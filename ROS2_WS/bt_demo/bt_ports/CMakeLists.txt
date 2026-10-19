cmake_minimum_required(VERSION 3.22)

project(bt_ports VERSION 1.0.0 LANGUAGES C CXX)

include(GNUInstallDirs)

include("${CMAKE_CURRENT_LIST_DIR}/cmake/ProjectOptions.cmake")

add_subdirectory(src)
