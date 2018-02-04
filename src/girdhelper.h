#ifndef __GIRDHELPER_H__
#define __GIRDHELPER_H__

#include "precomp.h"


void imdrawline(Mat mat);

Rect createRect(Point point, Size size);

Mat imsub(Mat& mat, Point point, Size size);

Mat imsubsquare(Mat& mat, Point point, int size);

void imresizeshow(Mat& mat, int size);

void subImageShow(Mat& mat, Point point, int size, int scale);

void imdrawgrid(Mat& mat, Point offset, Size size, Size count);

#endif