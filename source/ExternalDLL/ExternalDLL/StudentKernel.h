#pragma once

#include "IntensityImageStudent.h"

class StudentKernel {
public:
	StudentKernel(double** values, int w, int h) : values(values), w(w), h(h), factor(1) {}
	StudentKernel(double** values, int w, int h, double factor) : values(values), w(w), h(h), factor(factor) {}
	IntensityImageStudent apply_on_image(IntensityImageStudent img);
private:
	double ** values;
	int w, h;
	double factor;
};