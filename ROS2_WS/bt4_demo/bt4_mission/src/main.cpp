#include "behaviortree_cpp/bt_factory.h"

#include <chrono>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

class BatteryOK : public BT::ConditionNode
{
public:
    BatteryOK(const std::string& name, const BT::NodeConfig& config)
        : BT::ConditionNode(name, config)
    {}

    static BT::PortsList providedPorts()
    {
        return {BT::InputPort<double>("level")};
    }

    BT::NodeStatus tick() override
    {
        auto level = getInput<double>("level");
        if (!level)
        {
            throw BT::RuntimeError("Cannot read input [level]: ", level.error());
        }
        if (!std::isfinite(level.value()) || level.value() < 0.0 || level.value() > 100.0)
        {
            throw std::runtime_error("battery level must be between 0 and 100");
        }
        const auto result = level.value() >= 30.0
                                ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
        std::cout << "[BatteryOK] level=" << level.value()
                  << " -> " << BT::toStr(result) << '\n';
        return result;
    }
};

class ChargeBattery : public BT::SyncActionNode
{
public:
    ChargeBattery(const std::string& name, const BT::NodeConfig& config)
        : BT::SyncActionNode(name, config)
    {}

    static BT::PortsList providedPorts()
    {
        return {BT::OutputPort<double>("level")};
    }

    BT::NodeStatus tick() override
    {
        // 本例把充电简化为一次数据更新，真实充电应实现为持续任务。
        auto written = setOutput("level", 80.0);
        if (!written)
        {
            throw BT::RuntimeError("Cannot write output [level]: ", written.error());
        }
        std::cout << "[ChargeBattery] level=80\n";
        return BT::NodeStatus::SUCCESS;
    }
};

class NavigateToGoal : public BT::StatefulActionNode
{
public:
    NavigateToGoal(const std::string& name, const BT::NodeConfig& config)
        : BT::StatefulActionNode(name, config)
    {}

    static BT::PortsList providedPorts()
    {
        return {BT::InputPort<std::string>("goal"),
                BT::InputPort<int>("ticks", 2, "每次导航尝试的检查次数"),
                BT::InputPort<int>("fail_attempts", 1, "模拟前几次尝试失败"),
                BT::OutputPort<std::string>("reached_goal")};
    }

    BT::NodeStatus onStart() override
    {
        auto goal = getInput<std::string>("goal");
        auto ticks = getInput<int>("ticks");
        auto failures = getInput<int>("fail_attempts");
        if (!goal)
        {
            throw BT::RuntimeError("Cannot read input [goal]: ", goal.error());
        }
        if (!ticks)
        {
            throw BT::RuntimeError("Cannot read input [ticks]: ", ticks.error());
        }
        if (!failures)
        {
            throw BT::RuntimeError("Cannot read input [fail_attempts]: ", failures.error());
        }
        if (goal.value().empty() || ticks.value() < 1 || failures.value() < 0)
        {
            throw std::runtime_error("invalid navigation simulation parameters");
        }

        goal_ = goal.value();
        required_ticks_ = ticks.value();
        failed_attempts_ = failures.value();
        completed_ticks_ = 0;
        // 每个节点实例分别保留尝试次数，用于模拟先失败、后成功。
        ++attempt_;
        std::cout << "[NavigateToGoal] start goal=" << goal_
                  << ", attempt=" << attempt_
                  << ", completed_ticks=" << completed_ticks_ << '\n';
        return BT::NodeStatus::RUNNING;
    }

    BT::NodeStatus onRunning() override
    {
        ++completed_ticks_;
        std::cout << "[NavigateToGoal] check goal=" << goal_
                  << ", attempt=" << attempt_
                  << ", completed_ticks=" << completed_ticks_
                  << '/' << required_ticks_ << '\n';
        if (completed_ticks_ < required_ticks_)
        {
            return BT::NodeStatus::RUNNING;
        }
        if (attempt_ <= failed_attempts_)
        {
            std::cout << "[NavigateToGoal] failed goal=" << goal_
                      << ", attempt=" << attempt_ << '\n';
            return BT::NodeStatus::FAILURE;
        }

        auto written = setOutput("reached_goal", goal_);
        if (!written)
        {
            throw BT::RuntimeError("Cannot write output [reached_goal]: ", written.error());
        }
        std::cout << "[NavigateToGoal] arrived goal=" << goal_
                  << ", attempt=" << attempt_ << '\n';
        return BT::NodeStatus::SUCCESS;
    }

    void onHalted() override
    {
        std::cout << "[NavigateToGoal] halted goal=" << goal_ << '\n';
        completed_ticks_ = 0;
    }

private:
    std::string goal_;
    int required_ticks_ = 0;
    int completed_ticks_ = 0;
    int failed_attempts_ = 0;
    int attempt_ = 0;
};

class ReportMission : public BT::SyncActionNode
{
public:
    ReportMission(const std::string& name, const BT::NodeConfig& config)
        : BT::SyncActionNode(name, config)
    {}

    static BT::PortsList providedPorts()
    {
        return {BT::InputPort<std::string>("pickup"),
                BT::InputPort<std::string>("dropoff")};
    }

    BT::NodeStatus tick() override
    {
        auto pickup = getInput<std::string>("pickup");
        auto dropoff = getInput<std::string>("dropoff");
        if (!pickup)
        {
            throw BT::RuntimeError("Cannot read input [pickup]: ", pickup.error());
        }
        if (!dropoff)
        {
            throw BT::RuntimeError("Cannot read input [dropoff]: ", dropoff.error());
        }
        std::cout << "[ReportMission] pickup=" << pickup.value()
                  << ", dropoff=" << dropoff.value() << '\n';
        return BT::NodeStatus::SUCCESS;
    }
};

BT::NodeStatus ReportFailure(BT::TreeNode&)
{
    std::cout << "[ReportFailure] transport mission failed\n";
    return BT::NodeStatus::SUCCESS;
}

int main()
{
    try
    {
        BT::BehaviorTreeFactory factory;
        factory.registerNodeType<BatteryOK>("BatteryOK");
        factory.registerNodeType<ChargeBattery>("ChargeBattery");
        factory.registerNodeType<NavigateToGoal>("NavigateToGoal");
        factory.registerNodeType<ReportMission>("ReportMission");
        factory.registerSimpleAction("ReportFailure", ReportFailure);

        auto blackboard = BT::Blackboard::create();
        blackboard->set("battery", 20.0);
        blackboard->set("pickup_goal", std::string("loading_area"));
        blackboard->set("dropoff_goal", std::string("unloading_area"));
        auto tree = factory.createTreeFromFile(BT_XML_PATH, blackboard);

        int root_tick = 1;
        std::cout << "[main] tick=" << root_tick << " begin\n";
        BT::NodeStatus result = tree.tickExactlyOnce();
        std::cout << "[main] tick=" << root_tick
                  << " -> " << BT::toStr(result) << '\n';
        while (result == BT::NodeStatus::RUNNING)
        {
            tree.sleep(std::chrono::milliseconds(100));
            ++root_tick;
            std::cout << "[main] tick=" << root_tick << " begin\n";
            result = tree.tickExactlyOnce();
            std::cout << "[main] tick=" << root_tick
                      << " -> " << BT::toStr(result) << '\n';
        }
        std::cout << "Tree result: " << BT::toStr(result) << '\n';
        if (result == BT::NodeStatus::SUCCESS)
        {
            std::cout << "[main] pickup_reached="
                      << blackboard->get<std::string>("pickup_reached") << '\n';
            std::cout << "[main] dropoff_reached="
                      << blackboard->get<std::string>("dropoff_reached") << '\n';
        }
        return result == BT::NodeStatus::SUCCESS ? 0 : 1;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 2;
    }
}