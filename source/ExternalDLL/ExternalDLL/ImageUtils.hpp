
#pragma once
#include "IntensityImageStudent.h"
#include "Point2D.h"
#include "StudentHistogram.hpp"

class ImageUtils {
public:
	static IntensityImageStudent subimage(const IntensityImage * image, const Point2D<double> left_top, const Point2D<double> right_down);
	static IntensityImageStudent edge_scale(const IntensityImage * image);
	static IntensityImageStudent inverse(const IntensityImage * image);
	static IntensityImageStudent threshold(const IntensityImage * image, Intensity T);
	static StudentHistogram histogram_from_x_axis(const IntensityImage * image, int x);
	static Intensity interpolate_first_order(const IntensityImage * image, double x, double y);
};