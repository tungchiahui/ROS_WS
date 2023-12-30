#include "rclcpp/rclcpp.hpp"
#include "base_interfaces_demo/srv/add_ints.hpp"

using base_interfaces_demo::srv::AddInts;
using namespace std::chrono_literals;

class AddIntsClient: public rclcpp::Node
{
  public:
    AddIntsClient():Node("add_ints_client_node_cpp")
    {
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"客户端节点创建！");
      client_ = this->create_client<AddInts>("add_ints");
    }

    bool connect_server()
    {
      while(client_->wait_for_service(1s) != true)
      {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"服务连接中!");

        if (rclcpp::ok() != true)
        {
          RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"强行终止客户端!");
          return false;
        }
      }
      return true;
    }

    rclcpp::Client<AddInts>::FutureAndRequestId send_request(int32_t num1,int32_t num2)
    {
      /*
        返回值 rclcpp::Client<base_interfaces_demo::srv::AddInts>::FutureAndRequestId
        入口参数 async_send_request(std::shared_ptr<base_interfaces_demo::srv::AddInts_Request> request)  //其实就相当于AddInts::Request类型
      */
      auto request = std::make_shared<AddInts::Request>();
      request->num1 = num1;
      request->num2 = num2;
      return client_->async_send_request(request);
    }

  private:
    rclcpp::Client<AddInts>::SharedPtr client_;
};

int main(int argc, char ** argv)
{
  if(argc != 3)
  {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"请提交两个整形数字!");
    return 1;
  }
  rclcpp::init(argc,argv);

  auto client = std::make_shared<AddIntsClient>();

  bool flag = client->connect_server();

  if (flag != true)
  {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"服务器连接失败，程序退出!");
    return 0;
  }
  
  auto future = client->send_request(atoi(argv[1]),atoi(argv[2]));

  if (rclcpp::spin_until_future_complete(client,future) == rclcpp::FutureReturnCode::SUCCESS)
  {
    RCLCPP_INFO(client->get_logger(),"响应成功! sum = %d",future.get()->sum);
  }
  else
  {
    RCLCPP_INFO(client->get_logger(),"响应失败!");
  }

  rclcpp::shutdown();
  return 0;
}
