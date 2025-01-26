#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

class MyNode: public rclcpp::Node
{
  public:
    MyNode():Node("time_node_cpp")
    {
      RCLCPP_INFO(this->get_logger(),"Hello World!");
      // demo_rate();
      // demo_time();
      // demo_duration();
      demo_opt();
    }
  private:
    void demo_rate()
    {
      rclcpp::Rate rate1(500ms);
      rclcpp::Rate rate2(1.0);
      // while(rclcpp::ok())
      // {
      //   RCLCPP_INFO(this->get_logger(),"休眠500ms");
      //   rate1.sleep();
      // }
      while(rclcpp::ok())
      {
        RCLCPP_INFO(this->get_logger(),"休眠1000ms");
        rate2.sleep();
      }
    }

    void demo_time()
    {
      rclcpp::Time time1(500000000L);
      rclcpp::Time time2(2,500000000L);
      rclcpp::Time right_now_1 = this->get_clock()->now();
      rclcpp::Time right_now_2 = this->now();

      RCLCPP_INFO(this->get_logger(),"s = %.2f , ns = %ld",time1.seconds(),time1.nanoseconds());
      RCLCPP_INFO(this->get_logger(),"s = %.2f , ns = %ld",time2.seconds(),time2.nanoseconds());
      RCLCPP_INFO(this->get_logger(),"s = %.2f , ns = %ld",right_now_1.seconds(),right_now_1.nanoseconds());
      RCLCPP_INFO(this->get_logger(),"s = %.2f , ns = %ld",right_now_2.seconds(),right_now_2.nanoseconds());
    }

    void demo_duration()
    {
      rclcpp::Duration duration1(1s);
      rclcpp::Duration duration2(2,500000000L);
      RCLCPP_INFO(this->get_logger(),"s = %.2f , ns = %ld",duration1.seconds(),duration1.nanoseconds());
      RCLCPP_INFO(this->get_logger(),"s = %.2f , ns = %ld",duration2.seconds(),duration2.nanoseconds());
    }

    void demo_opt()
    {
      rclcpp::Time t1(10,0);
      rclcpp::Time t2(30,0);

      rclcpp::Duration du1(8,0);
      rclcpp::Duration du2(17,0);

      RCLCPP_INFO(this->get_logger(),"t1 >= t2 ? %d",t1 >= t2);
      RCLCPP_INFO(this->get_logger(),"t1 < t2 ? %d",t1 < t2);

      rclcpp::Duration du3 = t2 - t1;
      rclcpp::Time t3 = t1 + du1;
      rclcpp::Time t4 = t1 - du1;

      RCLCPP_INFO(this->get_logger(),"du3 = %.2f", du3.seconds());
      RCLCPP_INFO(this->get_logger(),"t3 = %.2f", t3.seconds());
      RCLCPP_INFO(this->get_logger(),"t4 = %.2f", t4.seconds());

      RCLCPP_INFO(this->get_logger(),"du1 >= du2 ? %d",du1 >= du2);
      RCLCPP_INFO(this->get_logger(),"du1 < du2 ? %d",du1 < du2);

      rclcpp::Duration du4 = du1 * 3;
      rclcpp::Duration du5 = du1 + du2;
      rclcpp::Duration du6 = du1 - du2;

      RCLCPP_INFO(this->get_logger(),"du4 = %.2f", du4.seconds());
      RCLCPP_INFO(this->get_logger(),"du5 = %.2f", du5.seconds());
      RCLCPP_INFO(this->get_logger(),"du6 = %.2f", du6.seconds());
    }
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc,argv);

  auto node = std::make_shared<MyNode>();

  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}