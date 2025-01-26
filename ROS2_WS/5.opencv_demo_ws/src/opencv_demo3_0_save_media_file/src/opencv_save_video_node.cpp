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
    template <typename T>
    bool Save_Video(T file_opened_name_or_index,const std::string & file_saved_name);
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
//    this->Save_Video<const std::string &>("./media/hei.mp4","./src/opencv_demo3_save_media_file/save_files/save_video_test1.mp4");
    this->Save_Video<int>(0,"./src/opencv_demo3_0_save_media_file/save_files/save_video_test2.mp4");
}
template <typename T>
bool OpenCV_Node::Save_Video(T file_opened_name_or_index,const std::string & file_saved_name)
{
    cv::Mat img;
    cv::VideoCapture video(file_opened_name_or_index);
    if(video.isOpened() == true)
    {
        RCLCPP_INFO(this->get_logger(),"调用摄像头或打开视频成功!");
        RCLCPP_INFO(this->get_logger(),"视频中图像的宽度=%lf",video.get(cv::CAP_PROP_FRAME_WIDTH));
        RCLCPP_INFO(this->get_logger(),"视频中图像的高度=%lf",video.get(cv::CAP_PROP_FRAME_HEIGHT));
        RCLCPP_INFO(this->get_logger(),"视频的帧率=%lf",video.get(cv::CAP_PROP_FPS));
        RCLCPP_INFO(this->get_logger(),"视频的总帧数=%lf",video.get(cv::CAP_PROP_FRAME_COUNT));
    }
    else
    {
        RCLCPP_INFO(this->get_logger(),"调用摄像头或者视频失败，请检查摄像头是否连接成功或者视频文件是否存在");
        return false;
    }
    video >> img;
    if(img.empty() == true)
    {
        RCLCPP_INFO(this->get_logger(),"帧图像获取失败!");
        return false;
    }
    cv::VideoWriter writer;
    auto file_name = file_saved_name;
    int codec = writer.fourcc('M','J','P','G');
    double fps = 30.0;
    auto size = img.size();
    bool isColor = (img.type() == CV_8UC3);
    writer.open(file_name,codec,fps,size,isColor);

    if(writer.isOpened() == true)  //判断视频流是否创建成功!
    {
        RCLCPP_INFO(this->get_logger(),"视频流创建成功!");
    }
    else
    {
        RCLCPP_INFO(this->get_logger(),"视频流创建失败，请确认是否为合法输入!");
        return false;
    }

    while(true)
    {
        if(video.read(img) == false)   //判断是否还能够继续从摄像头或者视频中读出一帧图像
        {
            RCLCPP_INFO(this->get_logger(),"摄像头断开连接或者视频读取完成!");
            break;
        }
        writer << img;  //writer.write(img);
        cv::namedWindow("Live");
        cv::imshow("Live",img);
        int8_t keyborad_value = cv::waitKey(1000 / video.get(cv::CAP_PROP_FPS));   //FPS为1秒每帧（也就是帧的数量），用1000ms / 帧的数量 = 每帧所需时间
        if(keyborad_value == 27)
        {
            break;
        }
    }
    video.release();
    writer.release();
    return true;
}