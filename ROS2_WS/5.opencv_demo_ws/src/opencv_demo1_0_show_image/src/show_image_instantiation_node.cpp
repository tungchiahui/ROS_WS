//ros2 pkg create opencv_demo1  --build-type ament_cmake --dependencies rclcpp OpenCV sensor_msgs cv_bridge image_transport --node-name opencv_node

#include "rclcpp/rclcpp.hpp"
#include "opencv2/opencv.hpp"

int main(int argc, char ** argv)
{
  rclcpp::init(argc,argv);
  auto opencv_node__ = rclcpp::Node::make_shared("opencv_node");

  cv::Mat picture_demo_mat = cv::imread("./media/林星阑L.jpg");
  cv::imshow("xiaoshen", picture_demo_mat);

  RCLCPP_INFO(opencv_node__->get_logger(),"ROS2用实例化的方式成功运行OpenCV!");

  cv::waitKey(0);   			// 这句确保窗口一直打开

  rclcpp::shutdown();
  return 0;
}






