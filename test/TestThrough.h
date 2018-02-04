#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/** @主函数 */
int MyMain(int argc, char** argv)
{
	/// 载入原图像和模板块
	Mat img = imread(argv[1], 1);

	Mat dst;
	Canny(img, dst, 50, 200, 3);
	Mat cdst = img.clone();

	namedWindow("ab1", CV_WINDOW_AUTOSIZE);
	imshow("ab1", dst);

	vector<Vec2f> lines;
	HoughLines(dst, lines, 1, CV_PI / 180, 100, 0, 0);

	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(cdst, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);
	}


	namedWindow("ab", CV_WINDOW_AUTOSIZE);
	imshow("ab", cdst);
	waitKey(0);

	return 0;
}
