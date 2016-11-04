#include "seetafaceDetect.h"
#include "TickCounter.h"
#include "utils.h"

seetafaceDetect::seetafaceDetect()
{
	detector = new seeta::FaceDetection("./seetaface/model/seeta_fd_frontal_v1.0.bin");
	align = new seeta::FaceAlignment("./seetaface/model/seeta_fa_v1.1.bin");
	recog = new seeta::FaceIdentification("./seetaface/model/seeta_fr_v1.0.bin");


	//featOld = new float[recog->feature_size()];
	featOld = NULL;
	detector->SetMinFaceSize(40);
	detector->SetScoreThresh(2.f);
	detector->SetImagePyramidScaleFactor(0.8f);
	detector->SetWindowStep(4, 4);

	//int fea_size = recog->feature_size();
	//float* feats1 = new float[fea_size];
	//float* feats2 = new float[fea_size];
}

seetafaceDetect::~seetafaceDetect()
{

}

vector<Rect> seetafaceDetect::detectAndDisplay(Mat& frame, double scale)
{
	vector<Rect> faceRects;

	CTickCounter tc(__FUNCTION__);

	Size dsize = Size(frame.cols * scale, frame.rows * scale);
	Mat img;
	resize(frame, img, dsize);

	Mat imgGray;
	cvtColor(img, imgGray, CV_BGR2GRAY);
	//equalizeHist( imgGray, imgGray );
	seeta::ImageData img_data(imgGray.cols, imgGray.rows, imgGray.channels());
	img_data.data = imgGray.data;

	vector<seeta::FaceInfo> faces;
	faces = detector->Detect(img_data);

	for (int i = 0; i < faces.size(); ++i)
	{
		Rect rc;
		rc.x = faces[i].bbox.x * 1.0 / scale;
		rc.y = faces[i].bbox.y * 1.0 / scale;
		rc.width = faces[i].bbox.width * 1.0 / scale;
		rc.height = faces[i].bbox.height * 1.0 / scale;

		boundCheckFaceRect(rc, frame.cols, frame.rows);


#if 0
		float* feat = GetFeature(img, faces[i]);
		printf("=========== %d\n", 2);
		if (NULL == featOld)
		{
			featOld = new float[recog->feature_size()];
		}
		else
		{
			float sim = FeatureCompare(featOld, feat);
			printf("=========== %f\n", sim);
		}
		memcpy(featOld, feat, recog->feature_size());
		free(feat);
#endif

		string words = CUtils::DoubleToString(faces[i].score);
		putText( frame, words, Point( rc.x, rc.y + rc.height - 5), CV_FONT_HERSHEY_SCRIPT_SIMPLEX, 1, Scalar(0, 255, 0) );
		//rectangle(frame, rc, Scalar(0, 0, 255), 1, 1, 0);
		faceRects.push_back(rc);
	}


	return faceRects;
}

float* seetafaceDetect::GetFeature(Mat& imgFace, seeta::FaceInfo faceinfo)
{
	CTickCounter tc(__FUNCTION__);
	float* feat = new float[recog->feature_size()];

	Mat imgGray;
	cvtColor(imgFace, imgGray, CV_BGR2GRAY);
	seeta::ImageData src_img_data(imgGray.cols, imgGray.rows, imgGray.channels());
	src_img_data.data = imgGray.data;


	seeta::ImageData src_img_data_color(imgFace.cols, imgFace.rows, imgFace.channels());
	src_img_data_color.data = imgFace.data;

	seeta::FacialLandmark points[5];
	align->PointDetectLandmarks(src_img_data, faceinfo, points);

	recog->ExtractFeatureWithCrop(src_img_data_color, points, feat);

	return feat;
}

float seetafaceDetect::FeatureCompare(float* feat1, float* feat2)
{
	CTickCounter tc(__FUNCTION__);
	return recog->CalcSimilarity(feat1, feat2);
}
