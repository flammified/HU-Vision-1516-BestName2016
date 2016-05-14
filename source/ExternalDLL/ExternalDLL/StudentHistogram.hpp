#pragma once

#include <vector>
#include "IntensityImage.h"
#include "ImageFactory.h"

class StudentHistogram {
public:
	StudentHistogram(int length);
	StudentHistogram(StudentHistogram& other);
	~StudentHistogram();
	int get_length();

	std::vector<int> peaks();
	void set_value(int x, double value);
	double get_value(int x);
	IntensityImage * get_debug_image();
private:
	double * histogram;
	int length;
};