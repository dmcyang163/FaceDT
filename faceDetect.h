#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

#include "opencv2/opencv.hpp"
using namespace cv;


class faceDetect
{
public:
	faceDetect() {};
	virtual ~faceDetect() {};

	virtual vector<Rect> detectAndDisplay(Mat& frame, double scale)
	{
		vector<Rect> rects;
		return rects;
	}


	template<typename T>
	void boundCheck(T& val, T min, T max)
	{
		if (val < min)
			val = min;
		if (val > max)
			val = max;
	}

	template<typename T>
	void boundCheckFaceRect(Rect& rc, T w, T h)
	{
		boundCheck(rc.x, 0, w);
		boundCheck(rc.y, 0, h);
		boundCheck(rc.width, 0, w);
		boundCheck(rc.height, 0, h);

		if ((rc.x + rc.width) > w)
			rc.width = w - rc.x;
		if ((rc.y + rc.height) > h)
			rc.height = h - rc.y;
	}
};

class cvfaceDetect: public faceDetect
{
public:
	cvfaceDetect();
	virtual ~cvfaceDetect();

	vector<Rect> detectAndDisplay(Mat& frame, double scale);


private:
	static string face_cascade_name;
	static String eyes_cascade_name;

	CascadeClassifier face_cascade;
	CascadeClassifier eyes_cascade;

};


