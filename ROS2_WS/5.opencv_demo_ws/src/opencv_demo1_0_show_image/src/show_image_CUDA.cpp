#include "rclcpp/rclcpp.hpp"
#include "opencv2/opencv.hpp"
#include <opencv2/core/cuda.hpp>

class OpenCV_Node: public rclcpp::Node   //rclcpp是命名空间 Node是一个父类  OpenCV_Node是一个子类
{
  public:
    OpenCV_Node();
    bool Show_Image_GPU_CUDA(void);
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
    this->Show_Image_GPU_CUDA();
}

bool OpenCV_Node::Show_Image_GPU_CUDA(void)
{
    cv::Mat picture_demo_mat = cv::imread("./media/林星阑H.jpg");
    cv::cuda::GpuMat gpuImage; 
    gpuImage.upload(picture_demo_mat); 
    cv::Mat result; 
    gpuImage.download(result);
    cv::namedWindow("林星阑",cv::WINDOW_NORMAL);
    cv::imshow("林星阑", result);
    RCLCPP_INFO(this->get_logger(),"ROS2节点:CUDA成功运行!");
    cv::waitKey(0);   			// 这句确保窗口一直打开
    return true;
}