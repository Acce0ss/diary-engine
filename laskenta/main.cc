#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <cstdlib>
#include <string>

int main(int argc, const char** argv) {

  cv::VideoCapture cap;

  if(argc > 1)
  {
    cap = cv::VideoCapture(argv[1]);
  }
  else
  {
    return EXIT_SUCCESS;
  }

  if(!cap.isOpened())
  {
    std::cout << "Cannot open video" << std::endl;
    return EXIT_FAILURE;
  }

  double fps = cap.get(CV_CAP_PROP_FPS);
  int width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
  int frame_count = cap.get(CV_CAP_PROP_FRAME_COUNT);



  double t_avg = 0;
  double t = 0;

  cv::Mat tmp_frame;


  for(int i = 0; i < frame_count; i++)
  {
    double t_tmp = (double)cv::getTickCount();

    cap >> tmp_frame;
    if(tmp_frame.empty())
    {
      std::cout << "Frame error" << std::endl;
      break;
    }

    t_tmp = ((double)cv::getTickCount() - t_tmp)/ cv::getTickFrequency();
    t += t_tmp;
    t_avg = t / (i+1);
  }

  std::cout << "Time taken in loop round: " << t_avg << " s (avg)." << std::endl;


  return EXIT_SUCCESS;
}
