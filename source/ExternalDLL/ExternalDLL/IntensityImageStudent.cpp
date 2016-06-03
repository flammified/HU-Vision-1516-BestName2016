#include "IntensityImageStudent.h"

IntensityImageStudent::IntensityImageStudent() : IntensityImage(){
	pixelmap = new Intensity[0];
	//int throwError = 0, e = 1 / throwError; //Throws error without the need to include a header
	//TODO: Nothing
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
	//int throwError = 0, e = 1 / throwError;
	//TODO: delete allocated objects
}

void IntensityImageStudent::set(const int width, const int height) {
    delete[] pixelmap;
    IntensityImage::set(width, height);
    pixelmap = new Intensity[width * height];

	//int throwError = 0, e = 1 / throwError;
	//TODO: resize or create a new pixel storage (Don't forget to delete the old storage)
}

void IntensityImageStudent::set(const IntensityImageStudent &other) {
    delete[] pixelmap;
	IntensityImage::set(other.getWidth(), other.getHeight());
	for (int i = 0; i < this->getHeight()*this->getWidth(); i++){
		pixelmap[i] = other.getPixel(i);
	}
	//int throwError = 0, e = 1 / throwError;
	//TODO: resize or create a new pixel storage and copy the object (Don't forget to delete the old storage)
}

void IntensityImageStudent::setPixel(int x, int y, Intensity pixel) {
	if (x < 0 || y < 0) return;
	if (!(x < this->getWidth() && y < this->getHeight())) return;
	pixelmap[y*this->getWidth() + x] = pixel;
	//int throwError = 0, e = 1 / throwError;
	//TODO: no comment needed :)
}

void IntensityImageStudent::setPixel(int i, Intensity pixel) {
	if (!(i < this->getWidth() * this->getHeight())) return;
	pixelmap[i] = pixel;
	//int throwError = 0, e = 1 / throwError;
	/*
	* TODO: set pixel i in "Row-Major Order"
	*
	*
	* Original 2d image (values):
	* 9 1 2
	* 4 3 5
	* 8 7 8
	*
	* 1d representation (i, value):
	* i		value
	* 0		9
	* 1		1
	* 2		2
	* 3		4
	* 4		3
	* 5		5
	* 6		8
	* 7		7
	* 8		8
	*/
}

Intensity IntensityImageStudent::getPixel(int x, int y) const {
	if (x < 0 || y < 0) return 255;
	if (!(x < this->getWidth() && y < this->getHeight())) return 255;
	return pixelmap[y*this->getWidth() + x];
	//int throwError = 0, e = 1 / throwError;
	//TODO: no comment needed :)
}

Intensity IntensityImageStudent::getPixel(int i) const {
	if (!(i < this->getWidth() * this->getHeight())) return Intensity();
	return pixelmap[i];
	//int throwError = 0, e = 1 / throwError;
	//TODO: see setPixel(int i, RGB pixel)
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