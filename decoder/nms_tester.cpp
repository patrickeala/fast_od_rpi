#include <iostream>
#include <string>
#include <fstream>
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
#include <vector>
#include <ctime>
#include <cmath>

#include "decode_detections.hpp"

using namespace std;
using namespace Eigen;


int main()
{

  const int y_pred_rows = 2006;
	const int y_pred_cols = 33;
  const int num_runs = 300;
  string filepath = "/home/patrick/Desktop/1secVOC/1Trial1/";
  string filename = "_y_pred_raw.txt";
  //double elapsedTotal = 0;
  float elapsedTotal = 0;
  MatrixXf y_pred(y_pred_rows, y_pred_cols);

  for(int k = 0; k < num_runs; k++)
  {
    ifstream currReadFile;
    string currFilename = filepath + to_string(k) + filename;
    currReadFile.open(currFilename);
    while (!currReadFile.eof()){
      for(int i = 0; i < y_pred_rows; i++){
        for (int j = 0; j < y_pred_cols; j++){
          currReadFile >> y_pred(i,j);
        }
      }
    }
    cout << "Decoding " << currFilename << " --- ";
    //double time_=cv::getTickCount();
    clock_t time_;
    time_ = clock();
    MatrixXf vec_boxes = decode_detections(y_pred, 0.3, 0.45, 4, 300, 300);
    //double secondsElapsed= double ( cv::getTickCount()-time_ ) /double ( cv::getTickFrequency() ); //time in second
    time_ = clock() - time_;
    float secondsElapsed = (float)time_/CLOCKS_PER_SEC; //time in seconds
    elapsedTotal += secondsElapsed;
    cout << "Elapsed Time: " << secondsElapsed << endl;
    cout << "vec_boxes:\n" << vec_boxes << endl;
  }

  cout<< elapsedTotal <<" seconds for "<< num_runs <<" images : FPS = "<< ( float ) ( ( float ) ( num_runs ) /elapsedTotal ) <<endl;
  return 0;
}
