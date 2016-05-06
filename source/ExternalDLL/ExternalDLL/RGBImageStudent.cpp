#include "RGBImageStudent.h"

RGBImageStudent::RGBImageStudent() : RGBImage() {
	pixelmap = new RGB[0];
}

RGBImageStudent::RGBImageStudent(const RGBImageStudent &other) : RGBImage{ other.getWidth(), other.getHeight() } {
	pixelmap = new RGB[this->getWidth() * this->getHeight()];
   for (int i = 0; i < this->getHeight()*this->getWidth(); i++) {
       pixelmap[i] = other.getPixel(i);
   }
}

RGBImageStudent::RGBImageStudent(const int width, const int height) : RGBImage(width, height) {
	pixelmap = new RGB[width * height];
}

RGBImageStudent::~RGBImageStudent() {
	delete[] pixelmap;
}

void RGBImageStudent::set(const int width, const int height) {
	delete[] pixelmap;
	RGBImage::set(width, height);
	pixelmap = new RGB[width * height];
}

void RGBImageStudent::set(const RGBImageStudent &other) {

	RGBImage::set(other.getWidth(), other.getHeight());
   for (int i = 0; i < this->getHeight()*this->getWidth(); i++) {
       pixelmap[i] = other.getPixel(i);
   }
}

void RGBImageStudent::setPixel(int x, int y, RGB pixel) {
    if (x < 0 || x >= getWidth() || y < 0 || y >= getHeight()) return; //should throw error
	pixelmap[y *this->getWidth() + x] = pixel;
}

void RGBImageStudent::setPixel(int i, RGB pixel) {
    if (i < 0 || i >= getHeight() * getWidth()) return;
	pixelmap[i] = pixel;
}

RGB RGBImageStudent::getPixel(int x, int y) const {
    x = x < 0 ? 0 : x;
    y = y < 0 ? 0 : y;
    x = x >= getWidth() ? getWidth() - 1 : x;
    y = y >= getHeight() ? getHeight() - 1 : y;
	return pixelmap[y*this->getWidth() + x];
}

RGB RGBImageStudent::getPixel(int i) const {
    i = i < 0 ? 0 : i;
    i = i >= getHeight()*getWidth() ? getHeight() * getWidth() - 1 : i;
	return pixelmap[i];
}