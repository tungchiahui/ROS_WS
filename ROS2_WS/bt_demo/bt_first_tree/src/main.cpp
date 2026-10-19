#include "behaviortree_cpp_v3/bt_factory.h"
#include <iostream>
#include <exception>
#include <string>

class SelectGoal : public BT::SyncActionNode
{
public:
    SelectGoal(const std::string& name, const BT::NodeConfiguration& config)
        : BT::SyncActionNode(name, config)
    {}

    static BT::PortsList providedPorts()
    {
        // 节点通过 goal 输出选定的目标
        return {BT::OutputPort<std::string>("goal")};
    }

    BT::NodeStatus tick() override
    {
        const std::string goal = "loading_area";
        setOutput<std::string>("goal", goal);
        std::cout << "[SelectGoal] goal=" << goal << '\n';
        return BT::NodeStatus::SUCCESS;
    }
};


class PrintGoal : public BT::SyncActionNode
{
public:
    PrintGoal(const std::string& name, const BT::NodeConfiguration& config)
        : BT::SyncActionNode(name, config)
    {}

    static BT::PortsList providedPorts()
    {
        // 节点需要一个名为 goal 的字符串输入
        return {BT::InputPort<std::string>("goal")};
    }

    BT::NodeStatus tick() override
    {
        // 每次执行时读取输入，读取成功后再使用
        auto goal = getInput<std::string>("goal");
        if (!goal)
        {
            throw BT::RuntimeError("Cannot read input [goal]: ", goal.error());
        }

        std::cout << "[PrintGoal] target=" << goal.value() << '\n';
        return BT::NodeStatus::SUCCESS;
    }
};

// 电量检查
BT::NodeStatus CheckBattery(BT::TreeNode&)
{
    // 修改这里的数值，可以模拟电量变化
    const double battery_level = 80.0;
    std::cout << "[CheckBattery] battery=" << battery_level << '\n';

    if (battery_level >= 20.0)
    {
        return BT::NodeStatus::SUCCESS;
    }
    return BT::NodeStatus::FAILURE;
}


int main()
{
    try
    {
        BT::BehaviorTreeFactory factory;
        factory.registerSimpleCondition("CheckBattery", CheckBattery);
        factory.registerNodeType<SelectGoal>("SelectGoal");
        factory.registerNodeType<PrintGoal>("PrintGoal");

        auto tree = factory.createTreeFromFile(BT_XML_PATH);
        const BT::NodeStatus result = tree.tickRoot();
        std::cout << "Tree result: " << BT::toStr(result) << '\n';

        return result == BT::NodeStatus::SUCCESS ? 0 : 1;
    }
    catch (const std::exception& error)
    {
        // 创建树或读取输入出错时，显示原因
        std::cerr << "Error: " << error.what() << '\n';
        return 2;
    }
}