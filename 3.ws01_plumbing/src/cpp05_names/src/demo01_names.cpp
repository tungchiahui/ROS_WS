#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using std_msgs::msg::String;

class MyNode: public rclcpp::Node
{
  public:
    MyNode():Node("mynode_node_name","t1_namespace")
    {
      RCLCPP_INFO(this->get_logger(),"Hello World!");
      publisher_ = this->create_publisher<String>("~/private_topics",10);
    }
  private:
    rclcpp::Publisher<String>::SharedPtr publisher_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc,argv);

  auto node = std::make_shared<MyNode>();

  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}