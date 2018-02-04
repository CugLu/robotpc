#include "precomp.h"
#include "test.h"
#include "girdhelper.h"

const static char* TEST_IMAGE = "res/test.jpg";
static Mat src;
static bool lbtndown = false;

void testRect()
{
	Rect r = createRect(Point(0, 0), Size(100, 100));
	printf("rect %d %d %d %d", r.x, r.y, r.width, r.height);
}

static void on_mouse(int event, int x, int y, int flags, void *ustc)
{
	if (event == CV_EVENT_LBUTTONDOWN)//左键按下，读取初始坐标，并在图像上该点处划圆  
	{
		lbtndown = true;
	}
	else if (event == CV_EVENT_LBUTTONUP)
	{
		lbtndown = false;
	}

	if (lbtndown)
	{
		Mat* img3 = (Mat*)ustc;

		Mat img = img3->clone();
		char temp[255];
		sprintf(temp, "(%d,%d)", x, y);
		Point pre_pt = Point(x, y);
		imshow("mouse", img);
		circle(img, pre_pt, 1, Scalar(255, 0, 0), -1);
		subImageShow(img, pre_pt, 50, 3);
		printf("on mouse %d %d\n", x, y);
	}
}

void testMouse()
{
	src = imread("res/test.jpg");
	namedWindow("mouse", CV_WINDOW_AUTOSIZE);
	setMouseCallback("mouse", on_mouse, &src);
	imshow("mouse", src);
}

void testBorder()
{
	src = imread(TEST_IMAGE);
	Mat dst;
	copyMakeBorder(src, dst, 5, 5, 5, 5, BORDER_CONSTANT, Scalar(255, 0, 0));
	imshow("border", dst);
}

void testResizeWindow()
{
	src = imread(TEST_IMAGE);
	imshow("border", src);
	resizeWindow("border", 500, 500);
}

void testDrawGrid()
{
	src = imread(TEST_IMAGE);
	imdrawgrid(src, Point(8, 208), Size(40, 40), Size(9, 9));
	imshow("gird", src);
}



void testmain()
{
	// testRect();

	// testBorder();

	testDrawGrid();

	//testMouse();

	// testResizeWindow();

	cvWaitKey();
}