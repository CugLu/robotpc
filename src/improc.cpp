#include "improc.h"

static int id = 0;
static char name[255];
static int alpha;
static Mat mat;

static void onChanged(int, void*)
{
	printf("aplha %d\n", alpha);
	Mat cur = mat.clone();
	line(cur, Point(1, alpha), Point(mat.cols, alpha), Scalar(255, 0, 0));
	imshow(name, cur);
}

void imdrawline(Mat src)
{
	mat = src;
	id++;
	alpha = 0;
	sprintf_s(name, "measure %d", id);
	namedWindow(name, CV_WINDOW_FREERATIO);

	imshow(name, mat);

	createTrackbar("t", name, &alpha, mat.rows, onChanged);
}


Mat imsubsquare(Mat& mat, Point point, int size)
{
	return imsub(mat, point, Size(size, size));
}

Mat imsub(Mat& mat, Point point, Size size)
{
	Rect r = createRect(point, size);

	r.x = std::max(0, r.x);
	r.y = std::max(0, r.y);
	r.width = std::min(mat.cols, r.width);
	r.height = std::min(mat.rows, r.height);

	return mat(r);
}


Rect createRect(Point point, Size size)
{
	return Rect(Point(point.x - size.width / 2, point.y - size.height / 2), size);
}

void imresizeshow(const char* name, Mat& mat, int size)
{
	Mat dst;
	resize(mat, dst, Size(size, size));
	imshow(name, dst);
}

void imshowsub(Mat& mat, Point point, int size, int scale)
{
	Mat src = imsubsquare(mat, point, size);
	Mat dst;
	resize(src, dst, Size(src.cols*scale, src.rows*scale));
	imshow("dst", dst);
}

void imdrawgrid(Mat& mat, Point offset, Size size, Size count)
{
	int w = mat.cols;
	int h = mat.rows;

	for (int i = 0; i < count.height; i++)
	{
		for (int j = 0; j < count.width; j++)
		{
			//cv::Mat mat = cv::Mat(image, cv::Rect(OFFSETX + i * WIDTH, OFFSETY + j*HEIHT, WIDTH, HEIGHT ));
			int left = offset.x + i * size.width;
			int botton = offset.y + j * size.height;

			rectangle(mat, Rect(left, botton, size.width, size.height), Scalar(0,0,255));
		}
	}
}
