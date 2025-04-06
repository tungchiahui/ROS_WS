cmake_minimum_required(VERSION 3.8)
project(opencv_demo3_0_save_media_file)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(OpenCV REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(image_transport REQUIRED)

add_executable(opencv_save_image_node src/opencv_save_image_node.cpp)
add_executable(opencv_save_image_in_video_node src/opencv_save_image_in_video_node.cpp)
add_executable(opencv_save_video_node src/opencv_save_video_node.cpp)
add_executable(opencv_save_XMLandYMAL src/opencv_save_XMLandYMAL.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/opencv_demo3_0_save_media_file)  #添加自己的头文件

target_include_directories(opencv_save_image_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

target_compile_features(opencv_save_image_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(
  opencv_save_image_node
  "rclcpp"
  "OpenCV"
  "sensor_msgs"
  "cv_bridge"
  "image_transport"
)

ament_target_dependencies(
  opencv_save_image_in_video_node
  "rclcpp"
  "OpenCV"
  "sensor_msgs"
  "cv_bridge"
  "image_transport"
)
ament_target_dependencies(
  opencv_save_video_node
  "rclcpp"
  "OpenCV"
  "sensor_msgs"
  "cv_bridge"
  "image_transport"
)
ament_target_dependencies(
  opencv_save_XMLandYMAL
  "rclcpp"
  "OpenCV"
  "sensor_msgs"
  "cv_bridge"
  "image_transport"
)

install(TARGETS opencv_save_image_node
  DESTINATION lib/${PROJECT_NAME})
install(TARGETS opencv_save_image_in_video_node
  DESTINATION lib/${PROJECT_NAME})
install(TARGETS opencv_save_video_node
  DESTINATION lib/${PROJECT_NAME})
install(TARGETS opencv_save_XMLandYMAL
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
