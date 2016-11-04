#include "faceDetect.h"
#include "TickCounter.h"


string cvfaceDetect::face_cascade_name = "/home/pi/tom/test/faceDT/haarcascade_frontalface_alt.xml";
String cvfaceDetect::eyes_cascade_name = "/home/pi/tom/test/faceDT/haarcascade_eye_tree_eyeglasses.xml";

cvfaceDetect::cvfaceDetect()
{
	if (!face_cascade.load(face_cascade_name)) {
		printf("[error] 无法加载级联分类器文件！\n");
	}
	if ( !eyes_cascade.load( eyes_cascade_name ) ) {
		printf("[error] 无法加载眼睛级联分类器文件！\n");
	}
}
cvfaceDetect::~cvfaceDetect()
{
}

vector<Rect> cvfaceDetect::detectAndDisplay(Mat& frame, double scale)
{
	CTickCounter tc("detectAndDisplay");
	vector<Rect> faceRects;


	Size dsize = Size(frame.cols * scale, frame.rows * scale);
	Mat framer;
	resize(frame, framer, dsize);

	Mat grayFrame;
	cvtColor( framer, grayFrame, CV_BGR2GRAY );
	equalizeHist( grayFrame, grayFrame );

	vector<Rect> faces;

	face_cascade.detectMultiScale( grayFrame, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30) );

	for ( int i = 0; i < faces.size(); i++ ) {
#if 0
		Mat faceROI = grayFrame( faces[i] );  //得到当前标注的脸部区域
		vector<Rect> eyes;//眼睛标注
		eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(10, 10) );
		for ( size_t j = 0; j < eyes.size(); j++ )
		{
			Point center( int(faces[i].x + eyes[j].x + eyes[j].width * 0.5), int(faces[i].y + eyes[j].y + eyes[j].height * 0.5) );
			center.x = center.x * 1.0 / scale;
			center.y = center.y * 1.0 / scale;
			int radius = cvRound( (eyes[j].width + eyes[i].height) * 0.25 );

			radius = radius * 1.0 / scale;
			circle( frame, center, radius, Scalar( 255, 0, 0 ), 1, 8, 0 );
		}
#endif
		//if (eyes.size() > 0)
		{
			Rect rc;
			rc.x = faces[i].x * 1.0 / scale;
			rc.y = faces[i].y * 1.0 / scale;
			rc.width = faces[i].width * 1.0 / scale;
			rc.height = faces[i].height * 1.0 / scale;

			boundCheckFaceRect(rc, frame.cols, frame.rows);

			//rectangle(frame, rc, Scalar(0, 0, 255), 1, 1, 0);
			faceRects.push_back(rc);
		}
	}

	return faceRects;
}


