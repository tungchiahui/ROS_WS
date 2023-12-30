#include <iostream>
#include "opencv2/opencv.hpp"
#include <opencv2/core/cuda.hpp>

int main(int argc,char **argv) 
{
  cv::Mat img = cv::imread("../素材/林星阑.jpg");
  if(img.empty() == false)
  {
    printf("成功读取图片!");
  }
  else
  {
    printf("无法读取图片，请确定图片文件是否存在，输入格式是否正确!");
    return false;
  }
  cv::Mat imgs[3];
  cv::Mat result[2];
  cv::split(img,imgs);
  cv::namedWindow("RGB-B通道",cv::WINDOW_FREERATIO);
  cv::namedWindow("RGB-G通道",cv::WINDOW_FREERATIO);
  cv::namedWindow("RGB-R通道",cv::WINDOW_FREERATIO);
  cv::imshow("RGB-B通道",imgs[0]);
  cv::imshow("RGB-G通道",imgs[1]);
  cv::imshow("RGB-R通道",imgs[2]);
  imgs[2] = img;  //改变图像通道数量
  cv::merge(imgs,3,result[0]);
  cv::namedWindow("合并图像结果0",cv::WINDOW_FREERATIO);
  cv::imshow("合并图像结果0",result[0]);   //不一定能看出来效果，需要Image Watch插件
  cv::Mat zero = cv::Mat::zeros(img.rows,img.cols,CV_8UC1);  //一个通道的0矩阵
  imgs[0] = zero;
  imgs[1] = zero;
  cv::merge(imgs,3,result[1]);
  cv::namedWindow("合并图像结果1",cv::WINDOW_FREERATIO);
  cv::imshow("合并图像结果1",result[1]);   //不一定能看出来效果，需要Image Watch插件
  cv::waitKey(0);
  return 0;
}