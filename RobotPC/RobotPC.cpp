// RobotPC.cpp : 定义控制台应用程序的入口点。
//
#include "precomp.h"

#include "resourcemgr.h"
#include "rimage.h"
#include "improc.h"
#include "test.h"

using namespace std;
using namespace cv;

int WIDTH = 40;
int HEIGHT = 40;
int OFFSETX = 8;
int OFFSETY = 168;


cv::Mat image;
HWND hWnd;

void templ()
{
	ResourceMgr* resMgr = new ResourceMgr();
	resMgr->addTrainData("res/xiaoji.png", XIAOJI);
	resMgr->addTrainData("res/maotouying.png", MAOTONGYING);
	resMgr->addTrainData("res/huli.png", HULI);
	resMgr->addTrainData("res/bingkuai.png", BINGKUAI);
	resMgr->addTrainData("res/mt.png", MT);
	resMgr->addTrainData("res/qingwa.png", QINGWA);

	image = image(cv::Rect(0, OFFSETY, image.cols, 400));

	RECT rect;
	GetWindowRect(hWnd, &rect);

	cv::Mat image_matched;

	cv::Mat templ = cv::imread("res/qingwa.png");

	cv::Mat img(cv::Size(image.cols, image.rows), CV_8UC3);
	cvtColor(image, img, CV_RGBA2RGB);
	cv::matchTemplate(img, templ, image_matched, CV_TM_SQDIFF);


	/// 通过函数 minMaxLoc 定位最匹配的位置
	double minVal; double maxVal; Point minLoc; Point maxLoc;
	Point matchLoc;

	minMaxLoc(image_matched, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
	matchLoc = minLoc;
	rectangle(img, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
	char buff[255];
	sprintf_s(buff, "%f", minVal);
	putText(img, buff, Point(100, 100), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0));

	cv::namedWindow("Capture");
	cv::imshow("Capture", img);

	cv::namedWindow("ab");
	cv::imshow("ab", image_matched);
}

int main(int argc, char* argv[])
{
	testmain();

	hWnd = findwindowlike("BlueStacks");
	if (hWnd == nullptr)
	{
		printf("no window like blue");
		return -1;
	}
	image = capturewindow(hWnd);



	imdrawline(image);

	//templ();
	cvWaitKey();

//	resMgr->matchTemplate(image);


	/*
	for (int i = 0; i < 9;i++)
	{
		for (int j = 0; j < 9; j++)
		{
			//cv::Mat mat = cv::Mat(image, cv::Rect(OFFSETX + i * WIDTH, OFFSETY + j*HEIHT, WIDTH, HEIGHT ));
			int left = OFFSETX + i * WIDTH;
			int top = OFFSETY + j * HEIGHT;
			cv::Mat mat = (*image)(cv::Range(top, top+HEIGHT), cv::Range(left, left + WIDTH));
			
			char file[255];
			sprintf_s(file, "%d_%d.jpg", i, j);
			cv::imwrite(file, mat);
		}
	}
	*/

	return 0;
}

