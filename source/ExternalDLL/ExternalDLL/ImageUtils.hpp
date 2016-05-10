#include "IntensityImageStudent.h"
#include "Point2D.h"

class ImageUtils {
public:
	static IntensityImageStudent subimage(const IntensityImage * image, const Point2D<double> left_top, const Point2D<double> right_down);
};