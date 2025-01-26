#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

class ParamClient: public rclcpp::Node
{
  public:
    ParamClient():Node("param_client_node_cpp")
    {
      RCLCPP_INFO(this->get_logger(),"参数客户端搭建!");
      param_client_ = std::make_shared<rclcpp::SyncParametersClient>(this,"param_server_node_cpp");
    }

    bool connect_server()
    {
      while(param_client_->wait_for_service(1s) != true)
      {
        if(rclcpp::ok() != true)
        {
          return false;
        }
        RCLCPP_INFO(this->get_logger(),"服务连接中!");
      }
      return true;
    }

    void get_param()
    {
      RCLCPP_INFO(this->get_logger(),"-----------参数查询操作-------------");
      //获取单个参数
      std::string car_name = param_client_->get_parameter<std::string>("car_name");
      double width = param_client_->get_parameter<double>("width");

      RCLCPP_INFO(this->get_logger(),"car_name = %s",car_name.c_str());
      RCLCPP_INFO(this->get_logger(),"width = %.2f",width);

      //获取多个参数
      auto params = param_client_->get_parameters({"car_name","width","wheels"});
      for (auto &&param : params)
      {
        RCLCPP_INFO(this->get_logger(),"%s = %s",param.get_name().c_str(),param.value_to_string().c_str());
      }
      
      //判断是否包含某个参数
      RCLCPP_INFO(this->get_logger(),"是否包含car_name? 答案:%d",param_client_->has_parameter("car_name"));
      RCLCPP_INFO(this->get_logger(),"是否包含height? 答案:%d",param_client_->has_parameter("height"));
      RCLCPP_INFO(this->get_logger(),"是否包含length? 答案:%d",param_client_->has_parameter("length"));
    }

    void update_param()
    {
      RCLCPP_INFO(this->get_logger(),"-----------参数更新操作-------------");
      param_client_->set_parameters({
        rclcpp::Parameter("car_name","RR"),
        rclcpp::Parameter("width",1.95),
        rclcpp::Parameter("length",5.0)
      });
    }

  private:
    rclcpp::SyncParametersClient::SharedPtr param_client_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc,argv);

  auto client = std::make_shared<ParamClient>();

  bool flag = client->connect_server();

  if(!flag)
  {
    return 0;
  }

  client->get_param();
  client->update_param();
  client->get_param();

  // rclcpp::spin(client);

  rclcpp::shutdown();
  return 0;
}