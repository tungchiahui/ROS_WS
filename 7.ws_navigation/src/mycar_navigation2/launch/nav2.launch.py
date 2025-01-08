import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    current_pkg = get_package_share_directory("mycar_navigation2")
    bt_params = os.path.join(get_package_share_directory("mycar_navigation2"),"params","bt.yaml")
    planner_params = os.path.join(get_package_share_directory("mycar_navigation2"),"params","planner.yaml")       
    controller_params = os.path.join(get_package_share_directory("mycar_navigation2"),"params","controller.yaml")       
    behavior_params = os.path.join(get_package_share_directory("mycar_navigation2"),"params","behavior.yaml")       
    waypoint_params = os.path.join(get_package_share_directory("mycar_navigation2"),"params","waypoint.yaml")       
    velocity_params = os.path.join(get_package_share_directory("mycar_navigation2"),"params","velocity.yaml")       
    smoother_params = os.path.join(get_package_share_directory("mycar_navigation2"),"params","smoother.yaml")       

    planner_server_node = Node(
        package='nav2_planner',
        executable='planner_server',
        name='planner_server',
        output='screen',
        parameters=[planner_params],
        )

    controller_server_node = Node(
        package='nav2_controller',
        executable='controller_server',
        output='screen',
        parameters=[controller_params],
        remappings=[('cmd_vel', 'cmd_vel_nav')]
    )

    behavior_server_node = Node(
        package='nav2_behaviors',
        executable='behavior_server',
        name='behavior_server',
        output='screen',
        parameters=[behavior_params]
    )

    waypoint_node = Node(
        package='nav2_waypoint_follower',
        executable='waypoint_follower',
        name='waypoint_follower',
        output='screen',
        parameters=[waypoint_params]
    )

    velocity_smoother_node = Node(
        package='nav2_velocity_smoother',
        executable='velocity_smoother',
        name='velocity_smoother',
        output='screen',
        respawn_delay=2.0,
        parameters=[velocity_params],
        remappings=
                [('cmd_vel', 'cmd_vel_nav'), ('cmd_vel_smoothed', 'cmd_vel')]
    )
    smoother_server_node = Node(
        package='nav2_smoother',
        executable='smoother_server',
        name='smoother_server',
        output='screen',
        parameters=[smoother_params],
    )
    bt_navigator_node = Node(
        package='nav2_bt_navigator',
        executable='bt_navigator',
        name='bt_navigator',
        output='screen',      
        parameters=[
            bt_params,
            {"default_nav_to_pose_bt_xml": os.path.join(current_pkg,"bts","bt_planner_controller_behavior.xml")},
            {"default_nav_through_poses_bt_xml": os.path.join(current_pkg,"bts","bt_planner_controller_behavior_poses.xml")}
            ],
        )

    lifecycle_manager_node = Node(
        package='nav2_lifecycle_manager',
        executable='lifecycle_manager',
        name='lifecycle_manager_navigation',
        output='screen',
        parameters=[{'use_sim_time': True},
                    {'autostart': True},
                    {'node_names': [
                        'bt_navigator',
                        'planner_server',
                        'controller_server',
                        'behavior_server',
                        'waypoint_follower',
                        'velocity_smoother',
                        'smoother_server'
                    ]}])

    return LaunchDescription([
        lifecycle_manager_node,
        bt_navigator_node,
        planner_server_node,
        controller_server_node,
        behavior_server_node,
        waypoint_node,
        velocity_smoother_node,
        smoother_server_node
    ])