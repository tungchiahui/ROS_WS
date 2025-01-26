#include "rclcpp/rclcpp.hpp"

class ParamServer: public rclcpp::Node
{
  public:
    ParamServer():Node("param_server_node_cpp",rclcpp::NodeOptions().allow_undeclared_parameters(true))
    {
      RCLCPP_INFO(this->get_logger(),"参数服务端搭建!");
    }

    void create_param()
    {
      RCLCPP_INFO(this->get_logger(),"-------------增操作--------------");

      this->declare_parameter("car_name","ER");
      this->declare_parameter("width",1.55);
      this->declare_parameter("wheels",5);

      this->set_parameter(rclcpp::Parameter("height",2.00));
    }

    void get_param()
    {
      RCLCPP_INFO(this->get_logger(),"-------------查操作--------------");

      auto car = this->get_parameter("car_name");
      RCLCPP_INFO(this->get_logger(),"key = %s,value = %s",car.get_name().c_str(),car.as_string().c_str()); 

      auto params = this->get_parameters({"car_name","width","wheels"});
      for(auto &&param : params)
      {
        RCLCPP_INFO(this->get_logger(),"key = %s,value = %s",param.get_name().c_str(),param.value_to_string().c_str()); 
      }
      
      bool car_name_flag = this->has_parameter("car_name");
      bool height_flag = this->has_parameter("height");
      RCLCPP_INFO(this->get_logger(),"是否包含car_name? 答案:%d",car_name_flag);
      RCLCPP_INFO(this->get_logger(),"是否包含height? 答案:%d",height_flag);
    }

    void update_param()
    {
      RCLCPP_INFO(this->get_logger(),"-------------改操作--------------");
      this->set_parameter(rclcpp::Parameter("width",1.85));
      RCLCPP_INFO(this->get_logger(),"width = %.2f",this->get_parameter("width").as_double());
    }

    void delete_param()
    {
      RCLCPP_INFO(this->get_logger(),"-------------删操作--------------");
    //   this->undeclare_parameter("car_name");
    //   RCLCPP_INFO(this->get_logger(),"是否包含car_name? 答案:%d",this->has_parameter("car_name"));
      this->undeclare_parameter("height");
      RCLCPP_INFO(this->get_logger(),"是否包含height? 答案:%d",this->has_parameter("height"));
    }


};

int main(int argc, char ** argv)
{
  rclcpp::init(argc,argv);

  auto node = std::make_shared<ParamServer>();

  node->create_param();
  node->get_param();
  node->update_param();
  node->delete_param();

  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}