from launch import LaunchDescription
from launch_ros.actions import Node

# 封装终端指令相关类
# from launch.actions import ExecuteProcess
# from launch.substitutions import FindExecutable
# 参数声明与获取
# from launch.actions import DeclareLaunchArgument
# from launch.substitutions import LaunchConfiguration
# 文件包含相关
# from launch.actions import IncludeLaunchDescription
# from launch.launch_description_sources import PythonLaunchDescriptionSource
# 分组相关
# from launch_ros.actions import PushRosNamespace
# from launch.actions import GroupAction
# 事件相关
# from launch.event_handlers import OnProcessStart,OnProcessExit
# from launch.actions import ExecuteProcess,RegisterEventHandler,LogInfo
# 获取功能包下share目录或路径
from ament_index_python.packages import get_package_share_directory

import os

def generate_launch_description():
    # turtle1 = Node(
    #     package="turtlesim",
    #     executable="turtlesim_node",
    #     exec_name="my_label",
    #     ros_arguments=["--remap","__ns:=/t2"]
    #     )
    turtle2 = Node(
        package="turtlesim",
        executable="turtlesim_node",
        name="haha",
        # parameters=[{"background_r": 255,"background_g": 0,"background_b": 0}],
        # parameters=["/home/tungchiahui/mysource/ros2src/4.ws02_tools/install/cpp01_launch/share/cpp01_launch/config/haha.yaml"],
        parameters=[os.path.join(get_package_share_directory("cpp01_launch"),"config","haha.yaml")],
        respawn=True
        )
    return LaunchDescription([turtle2])