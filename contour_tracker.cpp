#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

int myContourTracker(cv::Mat &map, std::vector<cv::Point2i> &contour, int nearber){
  static cv::Point direction8[16]={
    cv::Point(-1,0),cv::Point(-1,1),cv::Point(0,1),cv::Point(1,1),
    cv::Point(1,0),cv::Point(1,-1),cv::Point(0,-1),cv::Point(-1,-1),
    cv::Point(-1,0),cv::Point(-1,1),cv::Point(0,1),cv::Point(1,1),
    cv::Point(1,0),cv::Point(1,-1),cv::Point(0,-1),cv::Point(-1,-1),
  };
  static cv::Point direction4[8]={
    cv::Point(-1,0),cv::Point(0,1), cv::Point(1,0),cv::Point(0,-1),
    cv::Point(-1,0),cv::Point(0,1), cv::Point(1,0),cv::Point(0,-1),
  };
  // get top left corner
  cv::Point2i start_corner=cv::Point2i(-1,-1);
  for(int y=0; y<map.rows; y++){
    for(int x=0; x<map.cols; x++){
      if(map.at<uint8_t>(y,x)!=0){
        start_corner=cv::Point(x,y);
        break;
      }
    }
    if(start_corner.x!=-1){
      break;
    }
  }
  if(start_corner.x==-1){
    cout << "error no find corner!" << endl;;
    return -1;
  }
  int this_direction=0;
  contour.push_back(start_corner);
  cv::Point this_border=start_corner;
  // 8 neighbourhood
  if(nearber==8){
    while(true){
      for(int i=0;i<8;i++){
        cv::Point next_check=this_border+direction8[this_direction+i];
        if(next_check.x<0||next_check.y<0||
           next_check.x>=map.cols||next_check.y>=map.rows){
          continue;
        }
        // try next direction
        if(map.at<uint8_t>(next_check)==0){
          continue;
        }
        // find next border
        else{
          contour.push_back(next_check);
          this_border=next_check;
          this_direction=this_direction+i-2;
          if(this_direction>=8) this_direction-=8;
          if(this_direction<0) this_direction+=8;
          break;
        }
      }
      // finish loop
      if(this_border==start_corner){
        break;
      }
    }
  }
  // 4 neighbourhood
  else{
    while(true){
      for(int i=0;i<4;i++){
        cv::Point next_check=this_border+direction4[this_direction+i];
        if(next_check.x<0||next_check.y<0||
           next_check.x>=map.cols||next_check.y>=map.rows){
          continue;
        }
        // try next direction
        if(map.at<uint8_t>(next_check)==0) continue;
        // find next border
        else{
          contour.push_back(next_check);
          this_border=next_check;
          this_direction=this_direction+i-1;
          if(this_direction>=4) this_direction-=4;
          if(this_direction<0) this_direction+=4;
          break;
        }
      }
      // finish loop
      if(this_border==start_corner){
        break;
      }
    }
  }
  return 0;
}

int main()
{
  cv::Mat img=cv::imread("../A.bmp",CV_8UC1);

  std::vector<cv::Point2i> contour;
  myContourTracker(img, contour, 8);

  cv::Mat show_contour=cv::Mat::zeros(img.size(),CV_8UC1);
  for(auto &p:contour){
    show_contour.at<uint8_t>(p)=255;
  }

  cv::imshow("show_img",img);
  cv::imshow("show_contour",show_contour);
  cv::waitKey();
  return 0;
}
