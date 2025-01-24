import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource


def generate_launch_description():

    amcl_pkg = get_package_share_directory("mycar_localization_omni")
    nav2_pkg = get_package_share_directory("mycar_navigation2_omni")

    amcl_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(amcl_pkg,'launch',
                                                    'mycar_loca.launch.py'))
        )

    nav2_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(nav2_pkg,'launch', 
                                                    'nav2.launch.py'))
        )

    ld = LaunchDescription()
    ld.add_action(amcl_launch)
    ld.add_action(nav2_launch)
    return ld