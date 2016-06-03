#include "ImageUtils.hpp"

IntensityImageStudent ImageUtils::subimage(const IntensityImage * image, const Point2D<double> left_top, const Point2D<double> right_down)
{
   int left_x = 0;
   int right_x = image->getWidth();

   int left_y = 0;
   int right_y = image->getHeight();

   if (left_top.getX() > right_down.getX()){
       left_x = right_down.getX();
       right_x = left_top.getX();
   }
   else if (left_top.getX() < right_down.getX()){
       left_x = left_top.getX();
       right_x = right_down.getX();
   }

   if (left_top.getY() > right_down.getY()){
       left_y = right_down.getY();
       right_y = left_top.getY();
   }
   else if (left_top.getY() < right_down.getY()){
       left_y = left_top.getY();
       right_y = right_down.getY();
   }

	IntensityImageStudent result(right_x - left_x, right_y - left_y);
	for (int y = left_y; y < right_y; y++) {
		for (int x = left_x; x < right_x; x++) {
			result.setPixel(x - left_x, y - left_y, image->getPixel(x, y));
		}
	}
	return result;
}

StudentHistogram ImageUtils::histogram_from_x_axis(const IntensityImage * image, int y)
{
	StudentHistogram histo(image->getWidth());
	for (int x = 0; x < image->getWidth(); x++) {
		histo.set_value(x, 255 - image->getPixel(x, y));
	}
	return histo;
}
