#include "rclcpp/rclcpp.hpp"
#include "base_interfaces_demo/srv/add_ints.hpp"

using base_interfaces_demo::srv::AddInts;

class AddIntsServer: public rclcpp::Node
{
  public:
    AddIntsServer():Node("add_ints_server_node_cpp")
    {
      RCLCPP_INFO(this->get_logger(),"服务端节点创建！");
      server_ = this->create_service<base_interfaces_demo::srv::AddInts>("add_ints",std::bind(&AddIntsServer::add_callback,this,std::placeholders::_1,std::placeholders::_2));
    }
  private:
    void add_callback(const AddInts::Request::SharedPtr req,AddInts::Response::SharedPtr res)
    {
      res->sum = req->num1 + (*req).num2;
      RCLCPP_INFO(this->get_logger(),"%d + %d = %d",req->num1,req->num2,res->sum);
    }
    rclcpp::Service<base_interfaces_demo::srv::AddInts>::SharedPtr server_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc,argv);

  rclcpp::spin(std::make_shared<AddIntsServer>());

  rclcpp::shutdown();
  return 0;
}
