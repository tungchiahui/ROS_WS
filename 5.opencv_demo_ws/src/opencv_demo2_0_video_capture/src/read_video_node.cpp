#include "rclcpp/rclcpp.hpp"
#include "opencv2/opencv.hpp"

class OpenCV_Node: public rclcpp::Node   //rclcpp是命名空间 Node是一个父类  OpenCV_Node是一个子类
{
  public:
    OpenCV_Node();
    bool Video_Capture(void);
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc,argv);

  auto opencv_node__ = std::make_shared<OpenCV_Node>();  //使用 make_shared 函数分配内存并返回 shared_ptr 指针

  rclcpp::spin(opencv_node__);

  rclcpp::shutdown();

  return 0;
}

OpenCV_Node::OpenCV_Node():Node("read_video_node")     //子类构造函数调用父类的构造函数来初始化子类对象的成员变量
{
  this->Video_Capture();
}

bool OpenCV_Node::Video_Capture(void)
{
        cv::VideoCapture video__("./media/hei.mp4");
        if(video__.isOpened() == true)  //判断视频是否导入成功
        {
          RCLCPP_INFO(this->get_logger(),"视频中图像的宽度=%lf",video__.get(cv::CAP_PROP_FRAME_WIDTH));
          RCLCPP_INFO(this->get_logger(),"视频中图像的高度=%lf",video__.get(cv::CAP_PROP_FRAME_HEIGHT));
          RCLCPP_INFO(this->get_logger(),"视频的帧率=%lf",video__.get(cv::CAP_PROP_FPS));
          RCLCPP_INFO(this->get_logger(),"视频的总帧数=%lf",video__.get(cv::CAP_PROP_FRAME_COUNT));
        }
        else
        {
          RCLCPP_INFO(this->get_logger(),"导入视频失败，请确认视频文件是否正确");
          return false;
        }

        while(true)
        {
          cv::Mat frame__;
          video__ >> frame__;
          if(frame__.empty() == true) //检测图像是不是空的，如果是空的，说明视频最后一帧也已经导入完了
          {
            break;
          }
          if(rclcpp::ok()==false)
          {
            RCLCPP_INFO(this->get_logger(),"程序任务已取消");
            return false;
          }
          cv::imshow("视频播放",frame__);
          cv::waitKey(1000 / video__.get(cv::CAP_PROP_FPS));   //FPS为1秒每帧（也就是帧的数量），用1000ms / 帧的数量 = 每帧所需时间
        }
        cv::waitKey(0);   			// 这句确保窗口视频播放完后一直打开，不关闭
        return true;
    }






