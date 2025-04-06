#include <iostream>
#include "opencv2/opencv.hpp"
#include <opencv2/core/cuda.hpp>


int main(int argc, char ** argv)
{
  (void)argc;
  (void)argv;

  cv::Mat picture_demo_mat = cv::imread("./media/林星阑H.jpg");
  cv::cuda::GpuMat gpuImage; 
  gpuImage.upload(picture_demo_mat); 
  cv::Mat result; 
  gpuImage.download(result);
  cv::namedWindow("林星阑",cv::WINDOW_NORMAL);
  cv::imshow("林星阑", result);
  std::cout << "CUDA成功运行!" << std::endl;
  cv::waitKey(0);   			// 这句确保窗口一直打开

  return 0;
}