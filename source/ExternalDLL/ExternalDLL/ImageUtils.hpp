#include "IntensityImageStudent.h"
#include "Point2D.h"
#include "StudentHistogram.hpp"

class ImageUtils {
public:
	static IntensityImageStudent subimage(const IntensityImage * image, const Point2D<double> left_top, const Point2D<double> right_down);
	static StudentHistogram histogram_from_x_axis(const IntensityImage * image, int x);
};