#ifndef __RIMAGE_H__
#define __RIMAGE_H__
#include "cv.h"

#define _AFXDLL//为了方便是用mfc类    
#include<afxwin.h>   

cv::Mat capturescreen();
cv::Mat capturewindow(HWND hWnd);

HWND findwindowlike(const char* name);

enum TILE_TYPE
{
	XIAOJI = 1,
	MAOTONGYING,
	HULI,
	MT,
	BINGKUAI,
	QINGWA,
};

#endif