#include "ros/ros.h"

class MyNode
{
public:
    MyNode()
    {
        nh_ = std::make_shared<ros::NodeHandle>("~");
        ROS_INFO("HelloWorld!");
    }

private:
    // ROS1 节点句柄
    std::shared_ptr<ros::NodeHandle> nh_;
};

int main(int argc, char** argv)
{
    setlocale(LC_ALL,"");  //设置编码
    ros::init(argc, argv, "mynode_node");  // 初始化节点并指定名称
    auto node = std::make_shared<MyNode>();
    ros::spin();       // 主线程处理回调
    return 0;
}
