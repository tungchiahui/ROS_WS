import rclpy

def main():
    rclpy.init()
    node = rclpy.create_node("helloworld_py_node")
    node.get_logger().info("hello world by python!")
    rclpy.shutdown()

if __name__ == '__main__':
    main()
