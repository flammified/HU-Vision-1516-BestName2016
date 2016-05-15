#include "ImageUtils.hpp"

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

IntensityImageStudent ImageUtils::zero_crossings(const IntensityImage * image)
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
			bool change_in_range = false;
			bool lowest = true;
			int current_pixel = image->getPixel(x, y);

			for (int i = 0; i < 4; i++) {

				int dx = deltas[i][0];
				int dy = deltas[i][1];
				if (x + dx < 0 || x + dx > image->getWidth()) continue;
				if (y + dy < 0 || y + dy > image->getHeight()) continue;

				int pixel_value = image->getPixel(x + dx, y + dy) - 127;

				bool c = ((pixel_value - 127) ^ (current_pixel - 127)) < 0;

				if (c) {
					if (abs(pixel_value) > abs(current_pixel)) {
						lowest = false;
					}
					change_in_range = true;
				}
			}
			result.setPixel(x, y, change_in_range && lowest ? 255 : 0);
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
