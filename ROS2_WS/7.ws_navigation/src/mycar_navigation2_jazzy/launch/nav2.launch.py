import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

from launch_ros.actions import Node
from launch_ros.descriptions import ParameterFile

from nav2_common.launch import RewrittenYaml


def generate_launch_description():

    use_sim_time_arg = DeclareLaunchArgument(
        'use_sim_time',
        default_value='false'
    )

    use_sim_time = LaunchConfiguration('use_sim_time')

    # 从这开始修改: Jazzy launch 读取 mycar_navigation2_jazzy 自己安装出来的配置
    current_pkg = get_package_share_directory("mycar_navigation2_jazzy")
    # 从这结束

    bt_params_file = os.path.join(current_pkg, "params", "bt.yaml")
    planner_params_file = os.path.join(current_pkg, "params", "planner.yaml")
    controller_params_file = os.path.join(current_pkg, "params", "controller.yaml")
    behavior_params_file = os.path.join(current_pkg, "params", "behavior.yaml")
    waypoint_params_file = os.path.join(current_pkg, "params", "waypoint.yaml")
    velocity_params_file = os.path.join(current_pkg, "params", "velocity.yaml")
    smoother_params_file = os.path.join(current_pkg, "params", "smoother.yaml")

    def rewrite_params(params_file):
        return ParameterFile(
            RewrittenYaml(
                source_file=params_file,
                root_key='',
                param_rewrites={
                    'use_sim_time': use_sim_time
                },
                convert_types=True
            ),
            allow_substs=True
        )

    bt_params = rewrite_params(bt_params_file)
    planner_params = rewrite_params(planner_params_file)
    controller_params = rewrite_params(controller_params_file)
    behavior_params = rewrite_params(behavior_params_file)
    waypoint_params = rewrite_params(waypoint_params_file)
    velocity_params = rewrite_params(velocity_params_file)
    smoother_params = rewrite_params(smoother_params_file)

    planner_server_node = Node(
        package='nav2_planner',
        executable='planner_server',
        name='planner_server',
        output='screen',
        parameters=[
            planner_params,
            {'use_sim_time': use_sim_time}
        ],
    )

    controller_server_node = Node(
        package='nav2_controller',
        executable='controller_server',
        name='controller_server',
        output='screen',
        parameters=[
            controller_params,
            {'use_sim_time': use_sim_time}
        ],
        remappings=[
            ('cmd_vel', 'cmd_vel_nav')
        ]
    )

    behavior_server_node = Node(
        package='nav2_behaviors',
        executable='behavior_server',
        name='behavior_server',
        output='screen',
        parameters=[
            behavior_params,
            {'use_sim_time': use_sim_time}
        ]
    )

    waypoint_node = Node(
        package='nav2_waypoint_follower',
        executable='waypoint_follower',
        name='waypoint_follower',
        output='screen',
        parameters=[
            waypoint_params,
            {'use_sim_time': use_sim_time}
        ]
    )

    velocity_smoother_node = Node(
        package='nav2_velocity_smoother',
        executable='velocity_smoother',
        name='velocity_smoother',
        output='screen',
        respawn_delay=2.0,
        parameters=[
            velocity_params,
            {'use_sim_time': use_sim_time}
        ],
        remappings=[
            ('cmd_vel', 'cmd_vel_nav'),
            ('cmd_vel_smoothed', 'cmd_vel')
        ]
    )

    smoother_server_node = Node(
        package='nav2_smoother',
        executable='smoother_server',
        name='smoother_server',
        output='screen',
        parameters=[
            smoother_params,
            {'use_sim_time': use_sim_time}
        ],
    )

    bt_navigator_node = Node(
        package='nav2_bt_navigator',
        executable='bt_navigator',
        name='bt_navigator',
        output='screen',
        parameters=[
            bt_params,
            {'use_sim_time': use_sim_time},
            {
                "default_nav_to_pose_bt_xml": os.path.join(
                    current_pkg,
                    "bts",
                    "bt_planner_controller_behavior.xml"
                )
            },
            {
                "default_nav_through_poses_bt_xml": os.path.join(
                    current_pkg,
                    "bts",
                    "bt_planner_controller_behavior_poses.xml"
                )
            }
        ],
    )

    lifecycle_manager_node = Node(
        package='nav2_lifecycle_manager',
        executable='lifecycle_manager',
        name='lifecycle_manager_navigation',
        output='screen',
        parameters=[
            {'use_sim_time': use_sim_time},
            {'autostart': True},
            {
                'node_names': [
                    'bt_navigator',
                    'planner_server',
                    'controller_server',
                    'behavior_server',
                    'waypoint_follower',
                    'velocity_smoother',
                    'smoother_server'
                ]
            }
        ]
    )

    return LaunchDescription([
        use_sim_time_arg,

        lifecycle_manager_node,
        bt_navigator_node,
        planner_server_node,
        controller_server_node,
        behavior_server_node,
        waypoint_node,
        velocity_smoother_node,
        smoother_server_node
    ])
