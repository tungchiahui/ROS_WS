//一、实例化
// #include "rclcpp/rclcpp.hpp"

// int main(int argc, char ** argv)
// {
//   rclcpp::init(argc,argv);

//   auto node = rclcpp::Node::make_shared("helloworld_node");

//   RCLCPP_INFO(node->get_logger(),"hello world!");

//   rclcpp::shutdown();

//   return 0;
// }


//二、继承
#include "rclcpp/rclcpp.hpp"

class MyNode: public rclcpp::Node   //rclcpp是命名空间 Node是一个父类  MyNode是一个子类
{
  public:
    MyNode():Node("node_name")     //子类构造函数调用父类的构造函数来初始化子类对象的成员变量
    {
      RCLCPP_INFO(this->get_logger(),"hello world!MyNode!");
    }
};

int main(int argc,char *argv[])
{
  rclcpp::init(argc,argv);
  auto node = std::make_shared<MyNode>();  //使用 make_shared 函数分配内存并返回 shared_ptr 指针
  rclcpp::shutdown();
  return 0;
}