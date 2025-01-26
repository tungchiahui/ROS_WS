cmake_minimum_required(VERSION 3.8)
project(opencv_demo3_1_color_space)

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

add_executable(image_split_and_merge_node src/image_split_and_merge_node.cpp)
add_executable(image_convert_color_space src/image_convert_color_space.cpp)

target_include_directories(image_split_and_merge_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

target_compile_features(image_split_and_merge_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

ament_target_dependencies(
  image_split_and_merge_node
  "rclcpp"
  "OpenCV"
  "sensor_msgs"
  "cv_bridge"
  "image_transport"
)

ament_target_dependencies(
  image_convert_color_space
  "rclcpp"
  "OpenCV"
  "sensor_msgs"
  "cv_bridge"
  "image_transport"
)

install(TARGETS image_split_and_merge_node
  DESTINATION lib/${PROJECT_NAME})
install(TARGETS image_convert_color_space
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
