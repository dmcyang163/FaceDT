#pragma once

#include "faceDetect.h"


#include "recognizer.h"
#include "face_detection.h"
#include "face_alignment.h"
#include "face_identification.h"



class seetafaceDetect: public faceDetect
{
public:
	seetafaceDetect();
	virtual ~seetafaceDetect();

	seeta::FaceIdentification 	*recog;
	seeta::FaceAlignment 		*align;
	seeta::FaceDetection 		*detector;

	vector<Rect> detectAndDisplay(Mat& frame, double scale);


	float* GetFeature(Mat& imgFace, seeta::FaceInfo faceinfo);
	float FeatureCompare(float* feat1, float* feat2);


	float* featOld;
private:


};