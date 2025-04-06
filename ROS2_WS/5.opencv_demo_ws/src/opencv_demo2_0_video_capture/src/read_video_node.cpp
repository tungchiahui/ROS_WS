#include <cstdio>
#include "opencv2/opencv.hpp"

int main(int argc, char ** argv)
{
  (void)argc;
  (void)argv;

  cv::VideoCapture video__("./media/hei.mp4");
  if(video__.isOpened() == true)  //判断视频是否导入成功
  {
    printf("视频中图像的宽度=%lf",video__.get(cv::CAP_PROP_FRAME_WIDTH));
    printf("视频中图像的高度=%lf",video__.get(cv::CAP_PROP_FRAME_HEIGHT));
    printf("视频的帧率=%lf",video__.get(cv::CAP_PROP_FPS));
    printf("视频的总帧数=%lf",video__.get(cv::CAP_PROP_FRAME_COUNT));
  }
  else
  {
    printf("导入视频失败，请确认视频文件是否正确");
    return 1;
  }

  while(true)
  {
    cv::Mat frame__;
    video__ >> frame__;
    if(frame__.empty() == true) //检测图像是不是空的，如果是空的，说明视频最后一帧也已经导入完了
    {
      break;
    }
    cv::imshow("视频播放",frame__);
    cv::waitKey(1000 / video__.get(cv::CAP_PROP_FPS));   //FPS为1秒每帧（也就是帧的数量），用1000ms / 帧的数量 = 每帧所需时间
  }
  cv::waitKey(0);   			// 这句确保窗口视频播放完后一直打开，不关闭

  return 0;
}









