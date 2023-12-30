//ros2 pkg create opencv_demo1  --build-type ament_cmake --dependencies rclcpp OpenCV sensor_msgs cv_bridge image_transport --node-name opencv_node

#include "rclcpp/rclcpp.hpp"
#include "opencv2/opencv.hpp"

class OpenCV_Node: public rclcpp::Node   //rclcpp是命名空间 Node是一个父类  OpenCV_Node是一个子类
{
  public:
    OpenCV_Node():Node("opencv_node")     //子类构造函数调用父类的构造函数来初始化子类对象的成员变量
    {
        cv::Mat picture_demo_mat = cv::imread("./media/林星阑L.jpg");
        cv::imshow("xiaoshen", picture_demo_mat);
        RCLCPP_INFO(this->get_logger(),"ROS2用继承的方式成功运行OpenCV!");
        cv::waitKey(0);   			// 这句确保窗口一直打开
    }
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc,argv);

  auto opencv_node__ = std::make_shared<OpenCV_Node>();  //使用 make_shared 函数分配内存并返回 shared_ptr 指针

  rclcpp::spin(opencv_node__);

  rclcpp::shutdown();

  return 0;
}






