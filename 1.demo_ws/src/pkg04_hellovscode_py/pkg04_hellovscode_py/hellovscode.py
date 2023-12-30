import rclpy

def main():
    rclpy.init()
    node = rclpy.create_node("hellovscode_py_node")
    node.get_logger().info("hello vscode by python!")
    rclpy.shutdown()

if __name__ == '__main__':
    main()
