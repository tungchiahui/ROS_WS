#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "base_interfaces_demo/action/progress.hpp"

using base_interfaces_demo::action::Progress;
using namespace std::chrono_literals;
using std::placeholders::_1;
using std::placeholders::_2;

class ProgressActionClient: public rclcpp::Node
{
  public:
    ProgressActionClient():Node("progress_action_server_node_cpp")
    {
      RCLCPP_INFO(this->get_logger(),"action客户端创建!");
      /*
      rclcpp_action::Client<ActionT>::SharedPtr create_client<ActionT,
      NodeT>(NodeT node, const std::string &name, 
      rclcpp::CallbackGroup::SharedPtr group = nullptr, 
      const rcl_action_client_options_t &options = rcl_action_client_get_default_options())
      */
      client_ = rclcpp_action::create_client<Progress>(this,"get_sum_topic");
    }

    void send_goal(int32_t num)
    {
      if(client_->wait_for_action_server(1s) != true)
      {
        RCLCPP_ERROR(this->get_logger(),"服务连接失败!");
        return;
      }

      /*
      std::shared_future<rclcpp_action::ClientGoalHandle<base_interfaces_demo::action::Progress>::SharedPtr> 
      async_send_goal(const base_interfaces_demo::action::Progress::Goal &goal, 
      const rclcpp_action::Client<base_interfaces_demo::action::Progress>::SendGoalOptions &options)
      */
      auto goal = Progress::Goal();
      goal.num = num;

      rclcpp_action::Client<Progress>::SendGoalOptions options;
      options.goal_response_callback = std::bind(&ProgressActionClient::goal_response_callback,this,_1);
      options.feedback_callback = std::bind(&ProgressActionClient::feedback_callback,this,_1,_2);
      options.result_callback = std::bind(&ProgressActionClient::result_callback,this,_1);

      auto future = client_->async_send_goal(goal,options);
    }

  void goal_response_callback(rclcpp_action::ClientGoalHandle<Progress>::SharedPtr goal_handle)
  {
    if(goal_handle == nullptr)
    {
      RCLCPP_INFO(this->get_logger(),"目标请求被服务端拒绝!");
    }
    else
    {
      RCLCPP_INFO(this->get_logger(),"目标处理中!");
    }
  }

  void feedback_callback(rclcpp_action::ClientGoalHandle<Progress>::SharedPtr goal_handle,std::shared_ptr<const Progress::Feedback> feedback)
  {
    (void)goal_handle;
    double progress = feedback->progress;
    int progress_int = (int) (progress * 100);
    RCLCPP_INFO(this->get_logger(),"当前进度为:%d%%",progress_int);

    // // 发送取消请求
    // auto future_cancel = client_->async_cancel_goal(goal_handle);
    // rclcpp::spin_until_future_complete(this->get_node_base_interface(), future_cancel);

    // if (future_cancel.wait_for(1s) == std::future_status::ready)
    // {
    //   RCLCPP_INFO(this->get_logger(), "终止请求已发送!");
    // } 
    // else
    // {
    //   RCLCPP_ERROR(this->get_logger(), "无法发送终止请求...");
    // }
  }

  void result_callback(const rclcpp_action::ClientGoalHandle<Progress>::WrappedResult & result)
  {
    if (result.code == rclcpp_action::ResultCode::SUCCEEDED)
    {
      RCLCPP_INFO(this->get_logger(),"最终结果为:%d",result.result->sum);
    }
    else if(result.code == rclcpp_action::ResultCode::ABORTED)
    {
      RCLCPP_INFO(this->get_logger(),"过程被中断!");
    }
    else if(result.code == rclcpp_action::ResultCode::CANCELED)
    {
      RCLCPP_INFO(this->get_logger(),"任务被取消!");
    }
    else
    {
      RCLCPP_INFO(this->get_logger(),"未知异常!");
    }
  }

  private:
    rclcpp_action::Client<Progress>::SharedPtr client_;
};

int main(int argc, char ** argv)
{
  if(argc != 2)
  {
    RCLCPP_ERROR(rclcpp::get_logger("rclcppp"),"请输入一个整形数字!");
    return 1;
  }
  rclcpp::init(argc,argv);

  auto node = std::make_shared<ProgressActionClient>();

  node->send_goal(atoi(argv[1]));

  rclcpp::spin(node);

  rclcpp::shutdown(); 
  return 0;
}