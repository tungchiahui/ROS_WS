# Install script for directory: /home/tungchiahui/user/mysource/ros2src/5.opencv_demo_ws/src/opencv_demo3_0_save_media_file

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/tungchiahui/user/mysource/ros2src/5.opencv_demo_ws/install/opencv_demo3_0_save_media_file")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
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
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/opencv_demo3_0_save_media_file/opencv_save_image_node" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/opencv_demo3_0_save_media_file/opencv_save_image_node")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/opencv_demo3_0_save_media_file/opencv_save_image_node"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/opencv_demo3_0_save_media_file" TYPE EXECUTABLE FILES "/home/tungchiahui/user/mysource/ros2src/5.opencv_demo_ws/build/opencv_demo3_0_save_media_file/opencv_save_image_node")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/opencv_demo3_0_save_media_file/opencv_save_image_node" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/opencv_demo3_0_save_media_file/opencv_save_image_node")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/opencv_demo3_0_save_media_file/opencv_save_image_node"
         OLD_RPATH "/usr/local/cuda-11.8/lib64:/opt/ros/humble/lib/x86_64-linux-gnu:/opt/ros/humble/lib:/usr/local/opencv-4.8.1/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/opencv_demo3_0_save_media_file/opencv_save_image_node")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/opencv_demo3_0_save_media_file/opencv_save_image_in_video_node" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/opencv_demo3_0_save_media_file/opencv_save_image_in_video_node")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/opencv_demo3_0_save_media_file/opencv_save_image_in_video_node"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/opencv_demo3_0_save_media_file" TYPE EXECUTABLE FILES "/home/tungchiahui/user/mysource/ros2src/5.opencv_demo_ws/build/opencv_demo3_0_save_media_file/opencv_save_image_in_video_node")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/opencv_demo3_0_save_media_file/opencv_save_image_in_video_node" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/opencv_demo3_0_save_media_file/opencv_save_image_in_video_node")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/opencv_demo3_0_save_media_file/opencv_save_image_in_video_node"
         OLD_RPATH "/usr/local/cuda-11.8/lib64:/opt/ros/humble/lib/x86_64-linux-gnu:/opt/ros/humble/lib:/usr/local/opencv-4.8.1/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/opencv_demo3_0_save_media_file/opencv_save_image_in_video_node")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/opencv_demo3_0_save_media_file/opencv_save_video_node" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/opencv_demo3_0_save_media_file/opencv_save_video_node")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/opencv_demo3_0_save_media_file/opencv_save_video_node"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/opencv_demo3_0_save_media_file" TYPE EXECUTABLE FILES "/home/tungchiahui/user/mysource/ros2src/5.opencv_demo_ws/build/opencv_demo3_0_save_media_file/opencv_save_video_node")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/opencv_demo3_0_save_media_file/opencv_save_video_node" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/opencv_demo3_0_save_media_file/opencv_save_video_node")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/opencv_demo3_0_save_media_file/opencv_save_video_node"
         OLD_RPATH "/usr/local/cuda-11.8/lib64:/opt/ros/humble/lib/x86_64-linux-gnu:/opt/ros/humble/lib:/usr/local/opencv-4.8.1/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/opencv_demo3_0_save_media_file/opencv_save_video_node")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/package_run_dependencies" TYPE FILE FILES "/home/tungchiahui/user/mysource/ros2src/5.opencv_demo_ws/build/opencv_demo3_0_save_media_file/ament_cmake_index/share/ament_index/resource_index/package_run_dependencies/opencv_demo3_0_save_media_file")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/parent_prefix_path" TYPE FILE FILES "/home/tungchiahui/user/mysource/ros2src/5.opencv_demo_ws/build/opencv_demo3_0_save_media_file/ament_cmake_index/share/ament_index/resource_index/parent_prefix_path/opencv_demo3_0_save_media_file")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/opencv_demo3_0_save_media_file/environment" TYPE FILE FILES "/opt/ros/humble/share/ament_cmake_core/cmake/environment_hooks/environment/ament_prefix_path.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/opencv_demo3_0_save_media_file/environment" TYPE FILE FILES "/home/tungchiahui/user/mysource/ros2src/5.opencv_demo_ws/build/opencv_demo3_0_save_media_file/ament_cmake_environment_hooks/ament_prefix_path.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/opencv_demo3_0_save_media_file/environment" TYPE FILE FILES "/opt/ros/humble/share/ament_cmake_core/cmake/environment_hooks/environment/path.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/opencv_demo3_0_save_media_file/environment" TYPE FILE FILES "/home/tungchiahui/user/mysource/ros2src/5.opencv_demo_ws/build/opencv_demo3_0_save_media_file/ament_cmake_environment_hooks/path.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/opencv_demo3_0_save_media_file" TYPE FILE FILES "/home/tungchiahui/user/mysource/ros2src/5.opencv_demo_ws/build/opencv_demo3_0_save_media_file/ament_cmake_environment_hooks/local_setup.bash")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/opencv_demo3_0_save_media_file" TYPE FILE FILES "/home/tungchiahui/user/mysource/ros2src/5.opencv_demo_ws/build/opencv_demo3_0_save_media_file/ament_cmake_environment_hooks/local_setup.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/opencv_demo3_0_save_media_file" TYPE FILE FILES "/home/tungchiahui/user/mysource/ros2src/5.opencv_demo_ws/build/opencv_demo3_0_save_media_file/ament_cmake_environment_hooks/local_setup.zsh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/opencv_demo3_0_save_media_file" TYPE FILE FILES "/home/tungchiahui/user/mysource/ros2src/5.opencv_demo_ws/build/opencv_demo3_0_save_media_file/ament_cmake_environment_hooks/local_setup.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/opencv_demo3_0_save_media_file" TYPE FILE FILES "/home/tungchiahui/user/mysource/ros2src/5.opencv_demo_ws/build/opencv_demo3_0_save_media_file/ament_cmake_environment_hooks/package.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/packages" TYPE FILE FILES "/home/tungchiahui/user/mysource/ros2src/5.opencv_demo_ws/build/opencv_demo3_0_save_media_file/ament_cmake_index/share/ament_index/resource_index/packages/opencv_demo3_0_save_media_file")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/opencv_demo3_0_save_media_file/cmake" TYPE FILE FILES
    "/home/tungchiahui/user/mysource/ros2src/5.opencv_demo_ws/build/opencv_demo3_0_save_media_file/ament_cmake_core/opencv_demo3_0_save_media_fileConfig.cmake"
    "/home/tungchiahui/user/mysource/ros2src/5.opencv_demo_ws/build/opencv_demo3_0_save_media_file/ament_cmake_core/opencv_demo3_0_save_media_fileConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/opencv_demo3_0_save_media_file" TYPE FILE FILES "/home/tungchiahui/user/mysource/ros2src/5.opencv_demo_ws/src/opencv_demo3_0_save_media_file/package.xml")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/tungchiahui/user/mysource/ros2src/5.opencv_demo_ws/build/opencv_demo3_0_save_media_file/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
