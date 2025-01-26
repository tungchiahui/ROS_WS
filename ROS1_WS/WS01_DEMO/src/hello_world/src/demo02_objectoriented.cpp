#include "ros/ros.h"

class MyNode
{
public:
    MyNode() : nh_("~")
    {
        ROS_INFO("HelloWorld!");
    }

private:
    // ROS1 节点句柄
    ros::NodeHandle nh_; 
};

int main(int argc, char** argv)
{
    setlocale(LC_ALL,"");  //设置编码
    ros::init(argc, argv, "mynode_node");  // 初始化节点并指定名称
    MyNode node;
    ros::spin();       // 主线程处理回调
    return 0;
}






// #include "rclcpp/rclcpp.hpp"

// class MyNode: public rclcpp::Node
// {
//   public:
//     MyNode():Node("mynode_node")
//     {
//       RCLCPP_INFO(this->get_logger(),"Hello World!");
//     }
// };

// int main(int argc, char ** argv)
// {
//   rclcpp::init(argc,argv);

//   auto node = std::make_shared<MyNode>();

//   rclcpp::spin(node);

//   rclcpp::shutdown();
//   return 0;
// }