#include "rimage.h"
#include <string.h>

cv::Mat capturescreen()
{
	return capturewindow(GetDesktopWindow());
}

cv::Mat capturewindow(HWND hWnd)
{
	int image_width;
	int image_height;
	int image_depth;
	int image_nchannels;

	RECT rect;
	GetWindowRect(hWnd, &rect);
	int right = rect.right;
	int left = rect.left;
	int top = rect.top;
	int bottom = rect.bottom;
	int nWidth, nHeight;
	HDC hSrcDC = NULL, hMemDC = NULL;
	HBITMAP hBitmap = NULL, hOldBitmap = NULL;

	//hSrcDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);
	hSrcDC = GetDC(hWnd);
	hMemDC = CreateCompatibleDC(hSrcDC);
	nWidth = right - left;
	nHeight = bottom - top;

	hBitmap = CreateCompatibleBitmap(hSrcDC, nWidth, nHeight);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

	BitBlt(hMemDC, 0, 0, nWidth, nHeight, hSrcDC, 0, 0, SRCCOPY);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);

	BITMAP bmp;
	BYTE *pBuffer;
	GetObject(hBitmap, sizeof(BITMAP), &bmp);
	image_nchannels = bmp.bmBitsPixel == 1 ? 1 : bmp.bmBitsPixel / 8;
	image_depth = bmp.bmBitsPixel == 1 ? IPL_DEPTH_1U : IPL_DEPTH_8U;
	image_width = bmp.bmWidth;
	image_height = bmp.bmHeight;

	pBuffer = new BYTE[image_width*image_height*image_nchannels];
	GetBitmapBits(hBitmap, image_height*image_width*image_nchannels, pBuffer);
	cv::Mat mat = cv::Mat(cvSize(image_width, image_height), CV_MAKETYPE(CV_8U, image_nchannels), pBuffer);

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);
	SelectObject(hSrcDC, hBitmap);
	DeleteDC(hMemDC);
	DeleteObject(hBitmap);

	return mat;
}


HWND findwindowlike(const char* name)
{
	HWND hWnd = FindWindow(NULL, NULL);
	while (hWnd != NULL)
	{
		char text[255];
		GetWindowTextA(hWnd, text, 255);
		if (strstr(text, name) != nullptr)
		{
			printf("find window %s", text);
			return hWnd;
		}

		hWnd = GetNextWindow(hWnd, 2);
	}

	return nullptr;
}

CvPoint MCVGetNextMinLoc(IplImage* result, int templatWidth, int templatHeight, double maxValIn, CvPoint lastLoc){

	int y, x;
	int startY, startX, endY, endX;

	//计算大矩形的坐标
	startY = lastLoc.y - templatHeight;
	startX = lastLoc.x - templatWidth;

	//计算大矩形的的坐标 
	endY = lastLoc.y + templatHeight;
	endX = lastLoc.x + templatWidth;

	//不允许矩形越界
	startY = startY < 0 ? 0 : startY;
	startX = startX < 0 ? 0 : startX;
	endY = endY > result->height - 1 ? result->height - 1 : endY;
	endX = endX > result->width - 1 ? result->width - 1 : endX;

	//将大矩形内部 赋值为最大值 使得 以后找的最小值 不会位于该区域  避免找到重叠的目标       
	for (y = startY; y < endY; y++){
		for (x = startX; x < endX; x++){
			cvSetReal2D(result, y, x, maxValIn);
		}
	}
	double minVal, maxVal;
	CvPoint minLoc, maxLoc;

	//查找result中的最小值 及其所在坐标        
	cvMinMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, NULL);
	return minLoc;
}
