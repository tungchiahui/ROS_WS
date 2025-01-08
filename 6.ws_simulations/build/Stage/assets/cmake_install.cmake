# Install script for directory: /home/tungchiahui/UserFloder/mysource/ROS/ROS2_WS/6.ws_simulations/src/Stage/assets

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/tungchiahui/UserFloder/mysource/ROS/ROS2_WS/6.ws_simulations/install/Stage")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RELEASE")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/stage/assets" TYPE FILE FILES
    "/home/tungchiahui/UserFloder/mysource/ROS/ROS2_WS/6.ws_simulations/src/Stage/assets/blue.png"
    "/home/tungchiahui/UserFloder/mysource/ROS/ROS2_WS/6.ws_simulations/src/Stage/assets/death.png"
    "/home/tungchiahui/UserFloder/mysource/ROS/ROS2_WS/6.ws_simulations/src/Stage/assets/green.png"
    "/home/tungchiahui/UserFloder/mysource/ROS/ROS2_WS/6.ws_simulations/src/Stage/assets/logo.png"
    "/home/tungchiahui/UserFloder/mysource/ROS/ROS2_WS/6.ws_simulations/src/Stage/assets/mains.png"
    "/home/tungchiahui/UserFloder/mysource/ROS/ROS2_WS/6.ws_simulations/src/Stage/assets/mainspower.png"
    "/home/tungchiahui/UserFloder/mysource/ROS/ROS2_WS/6.ws_simulations/src/Stage/assets/question_mark.png"
    "/home/tungchiahui/UserFloder/mysource/ROS/ROS2_WS/6.ws_simulations/src/Stage/assets/red.png"
    "/home/tungchiahui/UserFloder/mysource/ROS/ROS2_WS/6.ws_simulations/src/Stage/assets/stagelogo.png"
    "/home/tungchiahui/UserFloder/mysource/ROS/ROS2_WS/6.ws_simulations/src/Stage/assets/stall-old.png"
    "/home/tungchiahui/UserFloder/mysource/ROS/ROS2_WS/6.ws_simulations/src/Stage/assets/stall.png"
    "/home/tungchiahui/UserFloder/mysource/ROS/ROS2_WS/6.ws_simulations/src/Stage/assets/rgb.txt"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/stage" TYPE FILE FILES "/home/tungchiahui/UserFloder/mysource/ROS/ROS2_WS/6.ws_simulations/src/Stage/assets/rgb.txt")
endif()

