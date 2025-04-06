//ros2 pkg create opencv_demo1  --build-type ament_cmake --dependencies rclcpp OpenCV sensor_msgs cv_bridge image_transport --node-name opencv_node
#include "opencv2/opencv.hpp"
#include <iostream>
#include <ostream>

int main(int argc, char ** argv)
{
  (void)argc;
  (void)argv;

  cv::Mat picture_demo_mat = cv::imread("./media/林星阑L.jpg");
  cv::imshow("xiaoshen", picture_demo_mat);

  std::cout << "成功运行OpenCV!" << std::endl; 

  cv::waitKey(0);   			// 这句确保窗口一直打开

  return 0;
}
