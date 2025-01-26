import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource


def generate_launch_description():

    slam_pkg = get_package_share_directory("mycar_slam_slam_toolbox")
    nav2_pkg = get_package_share_directory("mycar_navigation2")

    slam_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(slam_pkg,'launch',
                                                    'online_sync_launch.py'))
        )

    # slam_launch = IncludeLaunchDescription(
    #     PythonLaunchDescriptionSource(os.path.join(slam_pkg,'launch',
    #                                                 'online_async_launch.py'))
    #     )

    nav2_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(nav2_pkg,'launch', 
                                                    'nav2.launch.py'))
        )

    ld = LaunchDescription()
    ld.add_action(slam_launch)
    ld.add_action(nav2_launch)
    return ld