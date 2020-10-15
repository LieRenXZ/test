#include<iostream>
#include<opencv2/opencv.hpp>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/video.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/ml.hpp" 
#include<vector>
#include<string>
using namespace cv;
using namespace std;

//图像 
 Mat frame;
//文件
 stringstream str;
//坐标
 int x ,y;

 int uart()
{
    HANDLE hcom;
    hcom = CreateFile("COM3",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
    if (hcom == INVALID_HANDLE_VALUE)
    {
		fprintf(stderr, "打开串口失败！\n");
        exit(0);
    }
    SetupComm(hcom,1024,1024);
    DCB dcb;
    GetCommState(hcom,&dcb);
    dcb.BaudRate = 9600;
    dcb.ByteSize = 8;
    dcb.Parity = 0;
    dcb.StopBits = 1;
    SetCommState(hcom,&dcb);
    //传递坐标值
    char data[]={x,y};
    DWORD dwWrittenLen = 0;
	int k=0;
    if(!WriteFile(hcom,data,8,&dwWrittenLen,NULL))
    {
       	fprintf(stderr, "发送数据失败！\n");
    }
		k++;
    return 0;
}

int m_cap()
{
    
    Mat a = imread(str);
    IplImage *image = cvLoadImage("str");
    resize(a, a, cv::Size(1000, 1000));
    Mat e,d,g;
    d.create(a.size(),a.type());
    cvtColor(a,g,COLOR_BGR2GRAY);
    blur(g,e,Size(3,3));
    Canny(e,e,50,50,3);//二值化，获得边缘
    vector<vector<Point>> contours;  
    vector<Vec4i> hierarchy; 
    vector<Point>point;
    findContours(e,contours,hierarchy,0,CV_CHAIN_APPROX_NONE);
    for(int i = 0;i < contours.size();i++)
    {
        int epsilon = 0.01*arcLength(contours[i],true);
        approxPolyDP(contours[i], point, epsilon, true);
    }//获得边缘点
    vector<Moments> mu(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mu[i] = moments(contours[i], false);
	}
    vector<Point2f> mc(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
        x = mc[i].x;
        y = mc[i].y;
    }//计算中心位置
    
    waitKey(0);
}
int main()
{
 //打开视频文件 
 VideoCapture capture("IMG_2223.mp4");
 //获取整个帧数 
 long totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);
 //设置开始帧,结束帧 
 long frameToStart = 1;
 capture.set(CV_CAP_PROP_POS_FRAMES, frameToStart);
 int frameToStop = totalFrameNumber;
 //获取帧率 
 double rate = capture.get(CV_CAP_PROP_FPS);
 //控制视频结束
 bool stop = false;
 //两帧间的间隔时间: 
 double delay = 1000 / rate;
 //currentFrame是在循环体中控制读取到指定的帧后循环结束的变量 
 long currentFrame = frameToStart;
 //滤波器的核 
 int kernel_size = 3;
 Mat kernel = Mat::ones(kernel_size, kernel_size, CV_32F) / (float)(kernel_size*kernel_size);
 while (!stop)
 {
 //读取下一帧 
 capture.read(frame)
 //写入文件
 
 str << currentFrame << ".jpg";
 cout << str.str() << endl;
 imwrite(str.str(), frame);
 m_cap();//处理该帧图片，获得坐标
 //在该处画矩形
rectangle(image,x,y,Scalar(255,0,0),2);
 //播放
 imshow("Extractedframe", frame);
 //串口
 uart();
 //按下ESC或者到达指定的结束帧后退出读取视频 
 if ((char)c == 27 || currentFrame > frameToStop)
 {
  stop = true;
 }
 currentFrame++;
 }
 
 //关闭视频文件 
 capture.release();
 waitKey(0);
 return 0;
	
}