#include <ctime>
#include <iostream>
#include <raspicam/raspicam_cv.h>
#include <opencv2/imgproc.hpp>
using namespace std;

int main (int argc, char **argv)
{
  time_t timer_begin,timer_end;
	raspicam::RaspiCam_Cv Camera;
	cv::Mat image;
  cv::Mat resized;
  
  
  //camera currently set to capture frames of BGR color matrix format
  Camera.set( cv::CAP_PROP_FORMAT, CV_8UC3 );

  cout<<"Opening Camera..."<<endl;
	if (!Camera.open()) {
    cerr<<"Error opening the camera"<<endl;
    return -1;
  }

  cout << "Starting display..."<< endl;
  cout << "Press ESC to begin bounding box prediction." << endl;

  cv::namedWindow("Camera View", cv::WINDOW_AUTOSIZE);

  //Test video-stream
  while(1){
    Camera.grab();
		Camera.retrieve(image);
    cv::resize(image, resized, cv::Size(640,480));
		cv::imshow("Camera View",resized);
    char c = cv::waitKey(1);
    if(c == 27) break;

  }
  cout << "Press ESC to end." << endl;

  //Proper pipeline
  while(1){
    Camera.grab();
		Camera.retrieve(image);
    cv::resize(image, resized, cv::Size(640,480));
    //To do: convert Mat resized to std::vector<uin8_t> to make compatible w/ tflite
    
    /**
        TFLITE INFERENCE METHOD CALL HERE.
    **/
    
    //To do: Draw bounding boxes on resized
		cv::imshow("Camera View",resized);
    
    char c = cv::waitKey(1);
    if(c == 27) break;
  }

  Camera.release();

}
