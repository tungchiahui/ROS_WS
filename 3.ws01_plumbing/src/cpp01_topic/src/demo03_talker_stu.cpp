#include "rclcpp/rclcpp.hpp"
#include "base_interfaces_demo/msg/student.hpp"

using namespace std::chrono_literals;

class TalkerStu: public rclcpp::Node
{
public:
    TalkerStu():Node("talkerstu_node_cpp"),age(0)
    {
      RCLCPP_INFO(this->get_logger(),"发布节点创建！");
      publisher_ = this->create_publisher<base_interfaces_demo::msg::Student>("chatter_stu",10);
      timer_ = this->create_wall_timer(500ms,std::bind(&TalkerStu::on_timer_callback,this));
    }
private:
    void on_timer_callback()
    {
        auto stu = base_interfaces_demo::msg::Student();
        stu.name = "葫芦娃";
        stu.age = age;
        stu.height = 2.20f;
        age++;
        publisher_->publish(stu);
        RCLCPP_INFO(this->get_logger(),"发布的消息:(%s,%d,%.2f)",stu.name.c_str(),stu.age,stu.height);
    }
    rclcpp::Publisher<base_interfaces_demo::msg::Student>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    int32_t age;
};


int main(int argc, char ** argv)
{
  rclcpp::init(argc,argv);

  rclcpp::spin(std::make_shared<TalkerStu>());

  rclcpp::shutdown();
  return 0;
}
