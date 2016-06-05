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

std::vector<int> StudentHistogram::peaks(int peaksize, int start, int scope)
{
   if (scope == 0) scope = get_length();
   if (scope + start > get_length()) scope = get_length() - start;
   if (start < 1) start = 1;
	std::vector<int> result;
	int last_value = 0;
	for (int i = start; i < start+scope && i < length -1; i++) {
       if ((histogram[i - 1] < histogram[i] && histogram[i] > histogram[i + 1] + peaksize) || (histogram[i - 1] + peaksize < histogram[i] && histogram[i] > histogram[i + 1])) {
			result.push_back(i);
		}
	}
	return result;
}

void StudentHistogram::cut_to_size(unsigned int start, unsigned int stop){
    if (start + stop > get_length() || start > stop)return;

    double * new_histo = new double[stop - start];
    for (int i = start; i < stop; i++){
        new_histo[i - start] = histogram[i];
    }
    delete[] histogram;
    histogram = new_histo;
    length = stop - start;
}

IntensityImage * StudentHistogram::get_debug_image()
{
	IntensityImage * debugImage = ImageFactory::newIntensityImage(length, 255);
	
   for (int i = 0; i < debugImage->getHeight()*debugImage->getWidth(); i++){
       debugImage->setPixel(i, 0);
   }

	for (int x = 0; x < length; x++) {
		//debugImage->setPixel(x, 254 - 0, 255);
		std::cout << histogram[x] << "\n";
		for (int y = 0; y < histogram[x]; y++) {
			debugImage->setPixel(x, 254 - y, 255);
		}
	}

	return debugImage;
}
