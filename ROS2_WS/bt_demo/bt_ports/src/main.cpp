#include "behaviortree_cpp_v3/bt_factory.h"

#include <cmath>
#include <exception>
#include <iomanip>
#include <iostream>
#include <string>

struct Pose2D
{
    double x;
    double y;
    double yaw;
};

// 统一坐标的打印方式，便于观察每一步的数据
std::ostream& operator<<(std::ostream& stream, const Pose2D& pose)
{
    return stream << '(' << pose.x << ", " << pose.y << ", " << pose.yaw << ')';
}

namespace BT
{
template <>
inline Pose2D convertFromString<Pose2D>(StringView text)
{
    // XML 中的位姿格式为 x;y;yaw，朝向单位为弧度
    const auto parts = splitString(text, ';');
    if (parts.size() != 3)
    {
        throw RuntimeError("Pose2D requires x;y;yaw");
    }

    Pose2D pose{
        convertFromString<double>(parts[0]),
        convertFromString<double>(parts[1]),
        convertFromString<double>(parts[2])};

    if (!std::isfinite(pose.x) || !std::isfinite(pose.y) || !std::isfinite(pose.yaw))
    {
        throw RuntimeError("Pose2D values must be finite");
    }
    return pose;
}
}  // namespace BT

class CalculateGoal : public BT::SyncActionNode
{
public:
    CalculateGoal(const std::string& name, const BT::NodeConfiguration& config)
        : BT::SyncActionNode(name, config)
    {}

    static BT::PortsList providedPorts()
    {
        return {
            BT::InputPort<Pose2D>("start"),
            BT::InputPort<double>("distance", 1.0, "前进距离，单位为米"),
            BT::OutputPort<Pose2D>("goal")};
    }

    BT::NodeStatus tick() override
    {
        const auto start = getInput<Pose2D>("start");
        const auto distance = getInput<double>("distance");
        if (!start)
        {
            throw BT::RuntimeError("Cannot read input [start]: ", start.error());
        }
        if (!distance)
        {
            throw BT::RuntimeError("Cannot read input [distance]: ", distance.error());
        }
        if (!std::isfinite(distance.value()) || distance.value() < 0.0)
        {
            throw BT::RuntimeError("Input [distance] must be finite and non-negative");
        }

        // 沿起始朝向计算目标，计算结果仍是一个 Pose2D 对象
        const Pose2D& origin = start.value();
        const Pose2D goal{
            origin.x + distance.value() * std::cos(origin.yaw),
            origin.y + distance.value() * std::sin(origin.yaw),
            origin.yaw};

        const auto written = setOutput<Pose2D>("goal", goal);
        if (!written)
        {
            throw BT::RuntimeError("Cannot write output [goal]: ", written.error());
        }
        std::cout << "[CalculateGoal] distance=" << distance.value()
                  << ", goal=" << goal << '\n';
        return BT::NodeStatus::SUCCESS;
    }
};

class OffsetGoal : public BT::SyncActionNode
{
public:
    OffsetGoal(const std::string& name, const BT::NodeConfiguration& config)
        : BT::SyncActionNode(name, config)
    {}

    static BT::PortsList providedPorts()
    {
        return {
            BT::BidirectionalPort<Pose2D>("goal"),
            BT::InputPort<double>("offset_x", 0.0, "目标在参考坐标系 x 方向的偏移")};
    }

    BT::NodeStatus tick() override
    {
        const auto input = getInput<Pose2D>("goal");
        const auto offset = getInput<double>("offset_x");
        if (!input)
        {
            throw BT::RuntimeError("Cannot read input [goal]: ", input.error());
        }
        if (!offset)
        {
            throw BT::RuntimeError("Cannot read input [offset_x]: ", offset.error());
        }
        if (!std::isfinite(offset.value()))
        {
            throw BT::RuntimeError("Input [offset_x] must be finite");
        }

        // 先修改本地副本，再通过双向端口写回同一个条目
        Pose2D goal = input.value();
        goal.x += offset.value();
        const auto written = setOutput<Pose2D>("goal", goal);
        if (!written)
        {
            throw BT::RuntimeError("Cannot write output [goal]: ", written.error());
        }
        std::cout << "[OffsetGoal] goal=" << goal << '\n';
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
        return {BT::InputPort<Pose2D>("target")};
    }

    BT::NodeStatus tick() override
    {
        const auto target = getInput<Pose2D>("target");
        if (!target)
        {
            throw BT::RuntimeError("Cannot read input [target]: ", target.error());
        }
        std::cout << "[PrintGoal:" << name() << "] target=" << target.value() << '\n';
        return BT::NodeStatus::SUCCESS;
    }
};

int main()
{
    try
    {
        // 在编辑器中修改这个模拟距离，再构建运行；XML 路径由构建配置提供
        const double distance = 2.0;
        std::cout << std::fixed << std::setprecision(2);

        // 外部程序在创建树之前，准备带有明确 C++ 类型的输入
        auto blackboard = BT::Blackboard::create();
        blackboard->set<Pose2D>("robot_pose", Pose2D{1.0, 2.0, 0.0});
        blackboard->set<double>("travel_distance", distance);

        BT::BehaviorTreeFactory factory;
        factory.registerNodeType<CalculateGoal>("CalculateGoal");
        factory.registerNodeType<OffsetGoal>("OffsetGoal");
        factory.registerNodeType<PrintGoal>("PrintGoal");
        auto tree = factory.createTreeFromFile(BT_XML_PATH, blackboard);

        const BT::NodeStatus result = tree.tickRootWhileRunning();
        std::cout << "Tree result: " << BT::toStr(result) << '\n';
        if (result == BT::NodeStatus::SUCCESS)
        {
            // 树执行后，外部程序可以从同一块 Blackboard 取得输出
            const Pose2D goal = blackboard->get<Pose2D>("mission_goal");
            std::cout << "[main] mission_goal=" << goal << '\n';
        }
        return result == BT::NodeStatus::SUCCESS ? 0 : 1;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 2;
    }
}