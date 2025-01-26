import os
from launch import LaunchDescription
from launch_ros.actions import Node
def generate_launch_description():
  map_file = os.path.join('map', 'my_map.yaml')
  map_server_node = Node(
      package='nav2_map_server',
      executable='map_server',
      name='map_server',
      output='screen',
      parameters=[{'use_sim_time': True},
                  {'yaml_filename':map_file}]
  )
  manager_mapper_node = Node(
    package='nav2_lifecycle_manager',
    executable='lifecycle_manager',
    name='lifecycle_manager_mapper',
    output='screen',
    parameters=[{'use_sim_time': True},
      {'autostart': True},
      {'node_names': ['map_server']}]
  )
  return LaunchDescription([map_server_node,manager_mapper_node])