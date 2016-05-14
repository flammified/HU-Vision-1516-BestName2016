#include "StudentHistogram.hpp"
#include <iostream>

StudentHistogram::StudentHistogram(int length) : length(length)
{
	histogram = new double[length];
	for (int i = 0; i < length; i++) {
		histogram[i] = 0;
	}
}

StudentHistogram::StudentHistogram(StudentHistogram& other)
{
	length = other.get_length();
	histogram = new double[other.get_length()];
	for (int i = 0; i < length; i++) {
		histogram[i] = other.get_value(i);;
	}
}

int StudentHistogram::get_length() {
	return length;
}


StudentHistogram::~StudentHistogram() {
	delete[] histogram;
}

void StudentHistogram::set_value(int x, double value)
{
	if (x < 0 || x > length) return;
	histogram[x] = value;
}

double StudentHistogram::get_value(int x)
{
	if (x < 0 || x > length) return 0;
	return histogram[x];
}

std::vector<int> StudentHistogram::peaks()
{
	std::vector<int> result;
	int last_value = 0;
	for (int i = 0; i < length; i++) {
		if (histogram[i] < last_value) {
			result.push_back(i);
		}
	}
	return result;
}


IntensityImage * StudentHistogram::get_debug_image()
{
	IntensityImage * debugImage = ImageFactory::newIntensityImage(length, 255);
	
	for (int x = 0; x < length; x++) {
		//debugImage->setPixel(x, 254 - 0, 255);
		std::cout << histogram[x] << "\n";
		for (int y = 0; y < histogram[x]; y++) {
			debugImage->setPixel(x, 254 - y, 255);
		}
	}

	return debugImage;
}
