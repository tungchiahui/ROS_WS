#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "base_interfaces_demo/action/progress.hpp"

using base_interfaces_demo::action::Progress;
using std::placeholders::_1;
using std::placeholders::_2;


class ProgressActionServer: public rclcpp::Node
{
  public:
    ProgressActionServer():Node("progress_action_server_node_cpp")
    {
      RCLCPP_INFO(this->get_logger(),"action服务端创建!");
      /*
      rclcpp_action::Server<ActionT>::SharedPtr create_server<ActionT,
      NodeT>(NodeT node,
      const std::string &name,
      rclcpp_action::Server<ActionT>::GoalCallback handle_goal,
      rclcpp_action::Server<ActionT>::CancelCallback handle_cancel,
      rclcpp_action::Server<ActionT>::AcceptedCallback handle_accepted,
      const rcl_action_server_options_t &options = rcl_action_server_get_default_options(),
      rclcpp::CallbackGroup::SharedPtr group = nullptr)
      */
      server_ = rclcpp_action::create_server<Progress>(
        this,
        "get_sum_topic",
        std::bind(&ProgressActionServer::handle_goal_callback,this,_1,_2),
        std::bind(&ProgressActionServer::handle_cancel_callback,this,_1),
        std::bind(&ProgressActionServer::handle_accepted_callback,this,_1)
        );
    }

    //std::function<GoalResponse(const GoalUUID &, std::shared_ptr<const typename ActionT::Goal>)>
    rclcpp_action::GoalResponse handle_goal_callback(const rclcpp_action::GoalUUID &uuid, std::shared_ptr<const Progress::Goal> goal)
    {
      (void)uuid;
      if(goal->num <= 1)
      {
        RCLCPP_INFO(this->get_logger(),"提交的目标值必须大于1!");
        return rclcpp_action::GoalResponse::REJECT;
      }
      RCLCPP_INFO(this->get_logger(),"提交的目标值合法!");
      return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }

    //std::function<CancelResponse(std::shared_ptr<ServerGoalHandle<ActionT>>)>
    rclcpp_action::CancelResponse handle_cancel_callback(std::shared_ptr<rclcpp_action::ServerGoalHandle<Progress>> goal_handle)
    {
      (void)goal_handle;
      RCLCPP_INFO(this->get_logger(),"接收到任务取消请求!");
      return rclcpp_action::CancelResponse::ACCEPT;
    }


    //std::function<void (std::shared_ptr<ServerGoalHandle<ActionT>>)>
    void execute_callback(std::shared_ptr<rclcpp_action::ServerGoalHandle<Progress>> goal_handle)
    {
      //void publish_feedback(std::shared_ptr<base_interfaces_demo::action::Progress_Feedback> feedback_msg)
      //goal_handle->publish_feedback();
      int num = goal_handle->get_goal()->num;
      int sum = 0;
      auto feedback = std::make_shared<Progress::Feedback>();
      auto result = std::make_shared<Progress::Result>();
      rclcpp::Rate rate(1.0);
      for (int32_t i = 1; i <= num; i++)
      {
        sum += i;
        double progress = i / (double)num;
        feedback->progress = progress;

        goal_handle->publish_feedback(feedback);
        RCLCPP_INFO(this->get_logger(),"连续反馈中，当前进度为:%.2f",progress);

        if(goal_handle->is_canceling() == true)
        {
          result->sum = sum;
          goal_handle->canceled(result);
          RCLCPP_INFO(this->get_logger(),"任务被取消了!");
          return;
        }

        rate.sleep();
      }
      

      //void succeed(std::shared_ptr<base_interfaces_demo::action::Progress_Result> result_msg)
      //goal_handle->succeed();

      if(rclcpp::ok() == true)
      {
        result->sum = sum;
        goal_handle->succeed(result);
        RCLCPP_INFO(this->get_logger(),"最终响应结果为:%d",sum);
      }

    }

    void handle_accepted_callback(std::shared_ptr<rclcpp_action::ServerGoalHandle<Progress>> goal_handle)
    {
      std::thread(std::bind(&ProgressActionServer::execute_callback,this,goal_handle)).detach();
    }

  private:
    rclcpp_action::Server<Progress>::SharedPtr server_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc,argv);

  rclcpp::spin(std::make_shared<ProgressActionServer>());

  rclcpp::shutdown(); 
  return 0;
}