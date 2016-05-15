#include "IntensityImageStudent.h"

IntensityImageStudent::IntensityImageStudent() : IntensityImage(){
	pixelmap = new Intensity[0];
}

IntensityImageStudent::IntensityImageStudent(const IntensityImageStudent &other) : IntensityImage{other.getWidth(), other.getHeight()} {
	pixelmap = new Intensity[other.getWidth() * other.getHeight()];
	for (int i = 0; i < this->getWidth() * this->getHeight(); i++) {
		pixelmap[i] = other.getPixel(i);
	}
}

IntensityImageStudent::IntensityImageStudent(const IntensityImage &other) : IntensityImage{ other.getWidth(), other.getHeight() } {
	pixelmap = new Intensity[other.getWidth() * other.getHeight()];
	for (int i = 0; i < this->getWidth() * this->getHeight(); i++) {
		pixelmap[i] = other.getPixel(i);
	}
}

IntensityImageStudent::IntensityImageStudent(const int width, const int height) : IntensityImage(width, height) {
	pixelmap = new Intensity[width * height]();
	//int throwError = 0, e = 1 / throwError;
	//TODO: Initialize pixel storage
}

IntensityImageStudent::~IntensityImageStudent() {
    delete[] pixelmap;
}

void IntensityImageStudent::set(const int width, const int height) {
    delete[] pixelmap;
    IntensityImage::set(width, height);
    pixelmap = new Intensity[width * height];
}

void IntensityImageStudent::set(const IntensityImageStudent &other) {

	IntensityImage::set(other.getWidth(), other.getHeight());
	for (int i = 0; i < this->getHeight()*this->getWidth(); i++){
		pixelmap[i] = other.getPixel(i);
	}
}

void IntensityImageStudent::setPixel(int x, int y, Intensity pixel) {
	if (x < 0 || y < 0) return;
	if (!(x < this->getWidth() && y < this->getHeight())) return;
	pixelmap[y*this->getWidth() + x] = pixel;
	//int throwError = 0, e = 1 / throwError;
	//TODO: no comment needed :)
}

void IntensityImageStudent::setPixel(int i, Intensity pixel) {
	if (i < 0 || i >= getHeight() * getWidth()) return;
	pixelmap[i] = pixel;
}

Intensity IntensityImageStudent::getPixel(int x, int y) const {
    x = x < 0 ? 0 : x;
    y = y < 0 ? 0 : y;
    x = x >= getWidth() ? getWidth() - 1 : x;
    y = y >= getHeight() ? getHeight() - 1 : y;
	return pixelmap[y*this->getWidth() + x];
}

Intensity IntensityImageStudent::getPixel(int i) const {
    i = i < 0 ? 0 : i;
    i = i >= getHeight()*getWidth() ? getHeight() * getWidth() - 1 : i;
	return pixelmap[i];
}

void IntensityImageStudent::convertFromRGB(const RGBImage &other, bool efficient){
    delete[] pixelmap;
    IntensityImage::set(other.getWidth(), other.getHeight());
    pixelmap = new Intensity[this->getHeight()*this->getWidth()];
    if (efficient){
        //code for efficient
        efficientRGBConversion(other);
    }
    else {
        //code for accurate
        accurateRGBConversion(other);
    }
}

void IntensityImageStudent::accurateRGBConversion(const RGBImage &other){
    RGB temp_rgb;
    for (int i = 0; i < this->getHeight()*this->getWidth(); i++){
        temp_rgb = other.getPixel(i);
        pixelmap[i] = static_cast<unsigned char>(sqrt(0.299 * temp_rgb.r * temp_rgb.r + 0.587 * temp_rgb.g * temp_rgb.g + 0.114 * temp_rgb.b * temp_rgb.b));
    }
}

void IntensityImageStudent::efficientRGBConversion(const RGBImage &other){
    RGB temp_rgb;
    for (int i = 0; i < this->getHeight()*this->getWidth(); i++){
        temp_rgb = other.getPixel(i);
        pixelmap[i] = (temp_rgb.r + temp_rgb.r + temp_rgb.g + temp_rgb.g + temp_rgb.g + temp_rgb.b) / 6;
    }
}