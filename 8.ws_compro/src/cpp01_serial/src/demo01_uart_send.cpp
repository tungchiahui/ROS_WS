#include "rclcpp/rclcpp.hpp"
#include "serial_driver/serial_driver.hpp"

class Serial_Node : public rclcpp::Node
{
public:
  Serial_Node() : Node("serial_node_cpp")
  {
    // 等设备准备好再初始化
    // std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // 串口设备名（根据实际设备调整）
    const std::string device_name = "/dev/ttyUSB0";

    RCLCPP_INFO(this->get_logger(), "Serial port Node Open!");
    // 创建串口配置对象
    // 波特率115200；不开启流控制；无奇偶效验；停止位1。
    drivers::serial_driver::SerialPortConfig config(
        9600,
        drivers::serial_driver::FlowControl::NONE,
        drivers::serial_driver::Parity::NONE,
        drivers::serial_driver::StopBits::ONE);
    
    // 初始化串口
    try
    {
      io_context_ = std::make_shared<drivers::common::IoContext>();
      // 初始化 serial_port_
      serial_port_ = std::make_shared<drivers::serial_driver::SerialDriver>(*io_context_);
      serial_port_->init_port(device_name, config);
      
      RCLCPP_INFO(this->get_logger(), "Using device: %s", serial_port_->port().get()->device_name().c_str());
      RCLCPP_INFO(this->get_logger(), "Baud_rate: %d", config.get_baud_rate());

      RCLCPP_INFO(this->get_logger(), "Serial port initialized");
      if (serial_port_->port()->is_open())
      {
        RCLCPP_INFO(this->get_logger(), "Serial port is open");
      }
      else
      {
        RCLCPP_ERROR(this->get_logger(), "Serial port failed to open");
      }
    }
    catch (const std::exception &e)
    {
      RCLCPP_ERROR(this->get_logger(), "Failed to initialize serial port: %s", e.what());
      return;
    }

    // 设置发送定时器
    send_timer_ = this->create_wall_timer(
        std::chrono::milliseconds(500),
        std::bind(&Serial_Node::send_message_timer_callback, this));
  }


  std::shared_ptr<drivers::common::IoContext> io_context_;

private:
  void send_message_timer_callback()
  {
    // 发送一串字符串
    const std::string message = "Hello from ROS 2!\n";
    std::vector<uint8_t> data(message.begin(), message.end());
    // std::vector<uint8_t> hex_data = {0x48, 0x65, 0x6C, 0x6C, 0x6F}; // "Hello" in ASCII
    RCLCPP_INFO(this->get_logger(), "Timer Running");
    auto port = serial_port_->port();

    if (port->is_open())
    {
      size_t bytes_sent_size = port->send(data);
      RCLCPP_INFO(this->get_logger(), "Sent: %s (%ld bytes)", message.c_str(), bytes_sent_size);
    }
    else
    {
      RCLCPP_ERROR(this->get_logger(), "Serial port is not available");
    }
  }

  std::shared_ptr<drivers::serial_driver::SerialDriver> serial_port_;
  rclcpp::TimerBase::SharedPtr send_timer_;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  auto node = std::make_shared<Serial_Node>();

  // 启动 IoContext 的事件循环
  std::thread io_thread([&node]() {
    node->io_context_->ios().run();
  });

  rclcpp::spin(node);

  // 停止 IoContext
  node->io_context_->waitForExit();
  if (io_thread.joinable()) {
    io_thread.join();
  }

  rclcpp::shutdown();
  return 0;
}