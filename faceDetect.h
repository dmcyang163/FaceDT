#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <list>
using namespace std;

#include "opencv2/opencv.hpp"
using namespace cv;


typedef map<int, list<Rect> > Int2Rects;
class faceDetect
{
public:
	faceDetect();
	virtual ~faceDetect();


	vector<Rect> detectAndDisplay(Mat& frame, double scale);


};