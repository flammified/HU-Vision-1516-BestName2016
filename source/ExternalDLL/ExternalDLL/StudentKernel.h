#pragma once

#include "IntensityImageStudent.h"

class StudentKernel {
public:
	StudentKernel(double** values, int w, int h, int shift) : values(values), w(w), h(h), factor(1), shift(shift) {}
	StudentKernel(double** values, int w, int h, int shift, double factor) : values(values), w(w), h(h), shift(shift), factor(factor) {}
	IntensityImageStudent apply_on_image(IntensityImage * img);
	IntensityImageStudent dilate(IntensityImage * img);
private:
	double ** values;
	int w, h;
	double factor;
	int shift;
};