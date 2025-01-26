cmake_minimum_required(VERSION 3.8)
project(cpp01_serial)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(serial_driver REQUIRED)

add_executable(demo01_uart_send src/demo01_uart_send.cpp)
add_executable(demo02_uart_receive src/demo02_uart_receive.cpp)
add_executable(demo03_uart src/demo03_uart.cpp)

target_include_directories(demo01_uart_send PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)

target_include_directories(demo02_uart_receive PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)

target_include_directories(demo03_uart PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)


target_compile_features(demo01_uart_send PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(
  demo01_uart_send
  "rclcpp"
  "serial_driver"
)

target_compile_features(demo02_uart_receive PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(
  demo02_uart_receive
  "rclcpp"
  "serial_driver"
)

target_compile_features(demo03_uart PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(
  demo03_uart
  "rclcpp"
  "serial_driver"
)

install(TARGETS demo01_uart_send
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS demo02_uart_receive
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS demo03_uart
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
