#include <iostream>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"

class OpenCV_Node: public rclcpp::Node   //rclcpp是命名空间 Node是一个父类  OpenCV_Node是一个子类
{
  public:
    OpenCV_Node();
  private:
    bool Convert_To_Color_Space(const std::string & file_name);
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc,argv);

  auto opencv_node__ = std::make_shared<OpenCV_Node>();  //使用 make_shared 函数分配内存并返回 shared_ptr 指针

  rclcpp::spin(opencv_node__);

  rclcpp::shutdown();

  return 0;
}

OpenCV_Node::OpenCV_Node():Node("OpenCV_Node")
{
    this->Convert_To_Color_Space("./media/林星阑H.jpg");
}

bool OpenCV_Node::Convert_To_Color_Space(const std::string & file_name)
{
    cv::Mat img = cv::imread(file_name);
    if(img.empty() == true)
    {
        RCLCPP_INFO(this->get_logger(),"请确认图像文件是否正确，请检查输入格式");
        return false;
    }
    else
    {
        RCLCPP_INFO(this->get_logger(),"图像成功读取!");
    }
    cv::Mat img32;
    cv::Mat gray,HSV,YUV,Lab;
    img.convertTo(img32,CV_32F,1.0/255);   //缩放因子:1.0/255指将现在的图像的范围转换为目标图像的范围需要乘以的因数
    cv::cvtColor(img32,HSV,cv::COLOR_BGR2HSV);
    cv::cvtColor(img32,YUV,cv::COLOR_BGR2YUV);
    cv::cvtColor(img32,Lab,cv::COLOR_BGR2Lab);
    cv::cvtColor(img32,gray,cv::COLOR_BGR2GRAY);


    cv::namedWindow("原图BGR",cv::WINDOW_FREERATIO);
    cv::namedWindow("HSV",cv::WINDOW_FREERATIO);
    cv::namedWindow("YUV",cv::WINDOW_FREERATIO);
    cv::namedWindow("Lab",cv::WINDOW_FREERATIO);
    cv::namedWindow("gray",cv::WINDOW_FREERATIO);
    cv::imshow("原图BGR",img32);
    cv::imshow("HSV",HSV);
    cv::imshow("YUV",YUV);
    cv::imshow("Lab",Lab);
    cv::imshow("gray",gray);
    cv::waitKey(0);
    
    return true;
}