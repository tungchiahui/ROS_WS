#include "behaviortree_cpp_v3/bt_factory.h"

#include <chrono>
#include <iostream>
#include <stdexcept>
#include <string>

class NavigationAllowed : public BT::ConditionNode
{
public:
    NavigationAllowed(const std::string& name, const BT::NodeConfiguration& config)
        : BT::ConditionNode(name, config)
    {}

    static BT::PortsList providedPorts()
    {
        return {BT::InputPort<bool>("allowed")};
    }

    BT::NodeStatus tick() override
    {
        auto allowed = getInput<bool>("allowed");
        if (!allowed)
        {
            throw BT::RuntimeError("Cannot read input [allowed]: ", allowed.error());
        }
        std::cout << "[NavigationAllowed] allowed="
                  << (allowed.value() ? "true" : "false") << '\n';
        return allowed.value() ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
    }
};

class NavigateToGoal : public BT::StatefulActionNode
{
public:
    NavigateToGoal(const std::string& name, const BT::NodeConfiguration& config)
        : BT::StatefulActionNode(name, config)
    {}

    static BT::PortsList providedPorts()
    {
        return {BT::InputPort<std::string>("goal"),
                BT::InputPort<int>("ticks", 3, "完成导航所需的 onRunning 调用次数")};
    }

    BT::NodeStatus onStart() override
    {
        auto goal = getInput<std::string>("goal");
        auto ticks = getInput<int>("ticks");
        if (!goal)
        {
            throw BT::RuntimeError("Cannot read input [goal]: ", goal.error());
        }
        if (!ticks)
        {
            throw BT::RuntimeError("Cannot read input [ticks]: ", ticks.error());
        }
        if (goal.value().empty() || ticks.value() < 1)
        {
            throw std::runtime_error("goal must not be empty and ticks must be positive");
        }

        goal_ = goal.value();
        required_ticks_ = ticks.value();
        completed_ticks_ = 0;
        // 真实导航通常在这里发送一次请求，本例只保存模拟任务状态。
        std::cout << "[NavigateToGoal] start goal=" << goal_ << '\n';
        return BT::NodeStatus::RUNNING;
    }

    BT::NodeStatus onRunning() override
    {
        // 每次只检查一步，立即把执行权交回行为树。
        ++completed_ticks_;
        std::cout << "[NavigateToGoal] progress=" << completed_ticks_
                  << '/' << required_ticks_ << '\n';
        if (completed_ticks_ >= required_ticks_)
        {
            std::cout << "[NavigateToGoal] arrived goal=" << goal_ << '\n';
            return BT::NodeStatus::SUCCESS;
        }
        return BT::NodeStatus::RUNNING;
    }

    void onHalted() override
    {
        // 真实导航在这里取消请求、停止当前任务并清理资源。
        std::cout << "[NavigateToGoal] halted goal=" << goal_
                  << ", progress=" << completed_ticks_ << '\n';
        completed_ticks_ = 0;
    }

private:
    std::string goal_;
    int required_ticks_ = 0;
    int completed_ticks_ = 0;
};

int main()
{
    // 先用 false 跑通；改为 true 后，在第二次根 tick 后禁止继续导航。
    const bool cancel_after_two_ticks = true;

    try
    {
        BT::BehaviorTreeFactory factory;
        factory.registerNodeType<NavigationAllowed>("NavigationAllowed");
        factory.registerNodeType<NavigateToGoal>("NavigateToGoal");

        auto blackboard = BT::Blackboard::create();
        blackboard->set("navigation_allowed", true);
        auto tree = factory.createTreeFromFile(BT_XML_PATH, blackboard);

        BT::NodeStatus result = BT::NodeStatus::RUNNING;
        int tick_count = 0;
        while (result == BT::NodeStatus::RUNNING)
        {
            std::cout << "--- tick " << ++tick_count << '\n';
            result = tree.tickRoot();
            std::cout << "Root returned: " << BT::toStr(result) << '\n';
            if (result != BT::NodeStatus::RUNNING)
            {
                break;
            }

            if (cancel_after_two_ticks && tick_count == 2)
            {
                blackboard->set("navigation_allowed", false);
                std::cout << "[main] navigation is no longer allowed\n";
                return 3;
            }
            // 等待放在主循环中，节点回调本身不长时间阻塞。
            tree.sleep(std::chrono::milliseconds(100));
        }

        std::cout << "Tree result: " << BT::toStr(result) << '\n';
        return result == BT::NodeStatus::SUCCESS ? 0 : 1;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 2;
    }
}