#include "resourcemgr.h"
#include <string.h>
#include <windows.h>
#include "opencv2/highgui/highgui.hpp"

bool ResourceMgr::addTrainData(string filepath, int result)
{
	cv::Mat mat = cv::imread(filepath);
	return addTrainData(mat, result);
}

bool ResourceMgr::addTrainData(const cv::Mat& mat, int result)
{
	TrainData* data = new TrainData;
	data->mat = mat;
	data->result = result;
	return addTrainData(data);
}

bool ResourceMgr::addTrainData(TrainData* data)
{
	if (data == nullptr)
		return false;

	for (int i = 0; i < datas.size(); ++i)
	{
		if (datas[i]->result == data->result)
			return false;
	}

	datas.push_back(data);

	return true;
}

bool ResourceMgr::matchTemplate(cv::Mat* src)
{
	cv::namedWindow("ab");
	for (int i = 0; i < datas.size(); ++i)
	{
		cv::Mat image_matched;
		cv::matchTemplate(*src, datas[i]->mat, image_matched, cv::TM_CCOEFF_NORMED);

		cv::imshow("ab", image_matched);
		cvWaitKey(0);
	}


	return true;
}

