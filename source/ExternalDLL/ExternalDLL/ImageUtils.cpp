#include "ImageUtils.hpp"
#include <algorithm>

IntensityImageStudent ImageUtils::subimage(const IntensityImage * image, const Point2D<double> left_top, const Point2D<double> right_down)
{
	int left_x = left_top.getX();
	int left_y = left_top.getY();
	int right_x = right_down.getX();
	int right_y = right_down.getY();
	if (left_x > right_x || left_y > right_y) {
		return *image;
	}
	IntensityImageStudent result(right_x - left_x, right_y - left_y);
	for (int y = left_y; y < right_y; y++) {
		for (int x = left_x; x < right_x; x++) {
			result.setPixel(x - left_x, y - left_y, image->getPixel(x, y));
		}
	}
	return result;
}

IntensityImageStudent ImageUtils::edge_scale(const IntensityImage * image)
{
	IntensityImageStudent result(*image);

	int deltas[4][2] = {
		{1, 0},
		{0, 1},
		{-1, 0},
		{0, -1}
	};

	for (int x = 0; x < image->getWidth(); x++) {
		for (int y = 0; y < image->getHeight(); y++) {
			
			int current_pixel = image->getPixel(x, y);

			if (current_pixel < 126) {
				current_pixel -= 127;
				current_pixel = abs(current_pixel);

				if (current_pixel > 5) {
					current_pixel = 255;
					result.setPixel(x, y, 255);
				}
				else {
					result.setPixel(x, y, current_pixel * 20);
				}
			}
			else {
				result.setPixel(x, y, 0);
			}
			//int change = -100;
			//bool change_in_range = false;

			//for (int i = 0; i < 4; i++) {

			//	int dx = deltas[i][0];
			//	int dy = deltas[i][1];
			//	if (x + dx < 0 || x + dx > image->getWidth()) continue;
			//	if (y + dy < 0 || y + dy > image->getHeight()) continue;
			//	
			//	int pixel_value = image->getPixel(x + dx, y + dy);

			//	bool change_in_sign = ((pixel_value - 127) ^ (current_pixel - 127)) < 0;

			//	if (change_in_sign) {
			//		change_in_range = true;
			//		if (((current_pixel) - abs(pixel_value)) > change) {
			//			change = current_pixel - pixel_value;
			//		}
			//	}

			//}
			////result.setPixel(x, y, (change > 8 && change_in_range) ? 0 : 255);
			//if (change > 5 && change_in_range) {
			//	result.setPixel(x, y, 0);
			//} else if (change_in_range && change > 0) {
			//	//std::cout << "Change: " << abs(change) << "\n";
			//	result.setPixel(x, y, 255 - (change * 10));
			//}
			//else {
			//	result.setPixel(x, y, 255);
			//}
	
		}
	}
	return result;
}

IntensityImageStudent ImageUtils::inverse(const IntensityImage * image)
{
	IntensityImageStudent result(*image);

	for (int x = 0; x < image->getWidth(); x++) {
		for (int y = 0; y < image->getHeight(); y++) {

			int current_pixel = image->getPixel(x, y);
			result.setPixel(x, y, 255 - current_pixel);
		}
	}
	return result;
}

IntensityImageStudent ImageUtils::threshold(const IntensityImage * image, Intensity T)
{
	IntensityImageStudent result(*image);
	
	for (int x = 0; x < image->getWidth(); x++) {
		for (int y = 0; y < image->getHeight(); y++) {
			result.setPixel(x, y, image->getPixel(x, y) > T ? 255 : 0);
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


Intensity ImageUtils::interpolate_first_order(const IntensityImage * image, double x, double y) {

	double dx = x - floor(x);
	double dy = y - floor(y);

	Intensity p = image->getPixel(floor(x), floor(y)) + (image->getPixel(ceil(x), floor(y)) - image->getPixel(floor(x), floor(y))) * dx;
	Intensity q = image->getPixel(floor(x), ceil(y)) + (image->getPixel(ceil(x), ceil(y)) - image->getPixel(floor(x), ceil(y))) * dx;

	//std::cout << "x: " << x << " y: " << y << "\n";

	return p + (q - p) * dy;
}





