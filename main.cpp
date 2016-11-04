#include <iostream>
#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

#include "faceDetect.h"
#include "seetafaceDetect.h"
#include "serv.h"
#include "imghelpers.h"
#include "TickCounter.h"
#include "utils.h"

#include <wiringPi.h>
void* setgpio(void *arg)
{
    digitalWrite(0, HIGH) ; delay (500) ;
    digitalWrite(0,  LOW) ; delay (50) ;
    return NULL;
}


CServ serv; // 传输对象
void SendImg(Mat& img)
{
    // 图像压缩成jpg
    Mat matc;
    cvtColor(img, matc, CV_BGR2RGB);
    int w = img.cols;
    int h = img.rows;
    unsigned char* rgb_buffer = matc.data;

    unsigned char* jpeg_buf = NULL;
    long unsigned int jpeg_len = 0;
    CImgHelpers::get_jpeg(&jpeg_buf, &jpeg_len, (char*)rgb_buffer, w, h, 3);

    // 发送jpg
    serv.SendBuf((char*)jpeg_buf, jpeg_len);
    printf("=========SendBuf=========%d\n", jpeg_len);
    free(jpeg_buf);
    jpeg_buf = NULL;
}

int main(int argc, char **argv)
{
    //string ip = CUtils::getIpAddress();
    //printf("%s\n", ip.c_str());


    if (! CUtils::isCpuMatch(""))
        return -1;

    wiringPiSetup();
    pinMode (0, OUTPUT);

    seetafaceDetect faceDT;

    VideoCapture cap(0);
    //cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
    //cap.set(CV_CAP_PROP_FRAME_HEIGHT, 720);
    if (!cap.isOpened())
    {
        printf("[error] 无法开启摄像头！\n");
        return -1;
    }


    vector<Rect> facesOld;
    Mat edges;
    Mat frame;
    for (;;)
    {
        cap >> frame; // get a new frame from camera
        if (frame.data == NULL)
            continue; //等到捕获到数据

        flip(frame, edges, 1);

        vector<Rect> faces;
        faces = faceDT.detectAndDisplay(edges, 0.3);

#define FACE_DISTANCE 100
        if (faces.size() > 0)
        {
            bool bSendImg = false;
            if (facesOld.size() > 0)
            {
                int distance = 0;
                for (int j = 0; j < faces.size(); ++j)
                {
                    Point pt;
                    pt.x = faces[j].x + faces[j].width / 2;
                    pt.y = faces[j].y + faces[j].height / 2;
                    for (int i = 0; i < facesOld.size(); ++i)
                    {
                        Point ptOld;
                        ptOld.x = facesOld[i].x + facesOld[i].width / 2;
                        ptOld.y = facesOld[i].y + facesOld[i].height / 2;
                        int dist = int(sqrt( pow((pt.x - ptOld.x), 2.0) + pow((pt.y - ptOld.y), 2.0) ));
                        distance = MIN(dist, distance);
                    }
                }
                if ( distance > FACE_DISTANCE )
                {
                    printf("%d\n", distance);
                    bSendImg = true;
                }
            }
            else
                bSendImg = true;

            if (bSendImg)
            {
                for (int i = 0; i < faces.size(); ++i)
                {

                    Mat roi_img = edges(faces[i]);
                    SendImg(roi_img);
                }
            }
        }

        facesOld = faces;
    }

    return 0;
}
