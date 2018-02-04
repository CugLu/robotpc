#ifndef __RESOURCEMGR_H__
#define __RESOURCEMGR_H__
#include "cv.h"
#include <vector>

using namespace std;
struct TrainData
{
	cv::Mat mat;
	int result;
};

class ResourceMgr
{
public:

	bool addTrainData(string filepath, int result);
	bool addTrainData(const cv::Mat& mat, int result);
	bool addTrainData(TrainData* data);

	bool matchTemplate(cv::Mat* src);
protected:
private:

	vector<TrainData*> datas;
};

#endif