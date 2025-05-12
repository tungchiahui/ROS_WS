from launch import LaunchDescription
from launch_ros.actions import Node

# 封装终端指令相关类
from launch.actions import ExecuteProcess
# from launch.substitutions import FindExecutable
# 参数声明与获取
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
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
from launch_ros.parameter_descriptions import ParameterValue
from launch.substitutions import Command,LaunchConfiguration
import os

def generate_launch_description():
    robot_name_in_model = 'fishbot'
    package_name = 'fishbot_description'
    # urdf_xacro_name = "fishbot_gazebo.urdf"
    world_name = "fishbot.world"

    pkg_share = get_package_share_directory(f"{package_name}")
    urdf_xacro_model_path = os.path.join(pkg_share, "urdf/xacro","fishbot.urdf.xacro")
    gazebo_world_path = os.path.join(pkg_share, f'world/{world_name}')
    default_rviz_config_path = os.path.join(pkg_share, 'rviz/rviz2.rviz')

    model = DeclareLaunchArgument(name="model", default_value=urdf_xacro_model_path)
    robot_description = ParameterValue(Command(["xacro ",LaunchConfiguration("model")]))

    # Start Gazebo server
    start_gazebo_cmd = ExecuteProcess(
        cmd=['gazebo', '--verbose','-s', 'libgazebo_ros_init.so', '-s', 'libgazebo_ros_factory.so',gazebo_world_path],
        output='screen')
        
    # Launch the robot
    spawn_entity_cmd = Node(
        package='gazebo_ros', 
        executable='spawn_entity.py',
        arguments=['-entity', robot_name_in_model,  '-topic', '/robot_description' ], output='screen')
    
    # Start Robot State publisher
    start_robot_state_publisher_cmd = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        parameters=[{"robot_description": robot_description}]
    )

    # Launch RViz
    start_rviz_cmd = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        output='screen',
        arguments=['-d', default_rviz_config_path]
        )


    return LaunchDescription([model,start_gazebo_cmd,spawn_entity_cmd,start_robot_state_publisher_cmd,start_rviz_cmd])