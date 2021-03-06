#ifndef __IMPROC_H__
#define __IMPROC_H__

#include "precomp.h"


void imdrawline(Mat mat);

Rect createRect(Point point, Size size);

Mat imsub(Mat& mat, Point point, Size size);

Mat imsubsquare(Mat& mat, Point point, int size);

void imresizeshow(Mat& mat, int size);

void imshowsub(Mat& mat, Point point, int size, int scale);

void imdrawgrid(Mat& mat, Point offset, Size size, Size count);

double imgetsim(const Mat& src1, const Mat& src2);

#endif