import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PythonExpression


def generate_launch_description():

    use_sim_time_arg = DeclareLaunchArgument(
        'use_sim_time',
        default_value='false'
    )

    slam_backend_arg = DeclareLaunchArgument(
        'slam_backend',
        default_value='cartographer',
        description='SLAM backend: slam_toolbox or cartographer'
    )

    use_sim_time = LaunchConfiguration('use_sim_time')
    slam_backend = LaunchConfiguration('slam_backend')

    slam_toolbox_pkg = get_package_share_directory("mycar_slam_slam_toolbox")
    cartographer_pkg = get_package_share_directory("mycar_slam_cartographer")
    # 从这开始修改: Jazzy auto_slam 引用 mycar_navigation2_jazzy，而不是 Humble 版本包
    nav2_pkg = get_package_share_directory("mycar_navigation2_jazzy")
    # 从这结束

    slam_toolbox_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(
                slam_toolbox_pkg,
                'launch',
                'online_sync_launch.py'
            )
        ),
        launch_arguments={
            'use_sim_time': use_sim_time
        }.items(),
        condition=IfCondition(
            PythonExpression(["'", slam_backend, "' == 'slam_toolbox'"])
        )
    )

    cartographer_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(
                cartographer_pkg,
                'launch',
                'cartographer.launch.py'
            )
        ),
        launch_arguments={
            'use_sim_time': use_sim_time
        }.items(),
        condition=IfCondition(
            PythonExpression(["'", slam_backend, "' == 'cartographer'"])
        )
    )

    nav2_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(
                nav2_pkg,
                'launch',
                'nav2.launch.py'
            )
        ),
        launch_arguments={
            'use_sim_time': use_sim_time
        }.items()
    )

    ld = LaunchDescription()
    ld.add_action(use_sim_time_arg)
    ld.add_action(slam_backend_arg)
    ld.add_action(slam_toolbox_launch)
    ld.add_action(cartographer_launch)
    ld.add_action(nav2_launch)
    return ld
