#include "rclcpp/rclcpp.hpp"
#include "opencv2/opencv.hpp"


int main(int argc, char ** argv)
{
    (void)argc;
    (void)argv;

    cv::VideoCapture video__(0);
    cv::Mat frame__;
    if(video__.isOpened() == true)  //判断视频是否导入成功
    {
        printf("视频中图像的宽度=%lf",video__.get(cv::CAP_PROP_FRAME_WIDTH));
        printf("视频中图像的高度=%lf",video__.get(cv::CAP_PROP_FRAME_HEIGHT));
        printf("视频的帧率=%lf",video__.get(cv::CAP_PROP_FPS));
        printf("视频的总帧数=%lf",video__.get(cv::CAP_PROP_FRAME_COUNT));
    }
    else
    {
        printf("导入摄像头视频失败，请确认摄像头是否正常打开");
        return 1;
    }
    printf("按下空格键截图!");
    printf("按下ESC结束播放!");
    while(true)
    {
        video__ >> frame__;
        cv::imshow("Live",frame__);
        int32_t key_boards_val = cv::waitKey(1000/video__.get(cv::CAP_PROP_FPS));
        if(key_boards_val==32)   //检测到按下了空格键
        {
            if(cv::imwrite("./src/opencv_demo3_0_save_media_file/save_files/save_image_test2.png",frame__) == false)
            {
                printf("截图失败!");
            }
            else
            {
                printf("截图成功!");
            }
            if(frame__.empty() == true) //检测图像是不是空的，如果是空的，说明视频最后一帧也已经导入完了
            {
                printf("视频播放结束,请选择截图或是按ESC退出!");
            }
        }
        else if(key_boards_val==27)   //检测到按下了ESC按键
        {
            break;
        }
    }
    video__.release();
    printf("播放被终止或已结束!");

    return 0;
}