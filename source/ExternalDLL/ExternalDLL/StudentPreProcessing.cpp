#include "StudentPreProcessing.h"
#include "IntensityImageStudent.h"
#ifndef EFFICIENT_RGB_CONVERSION
//#define EFFICIENT_RGB_CONVERSION
#endif

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
    IntensityImage * new_intensity = new IntensityImageStudent{ image.getWidth(), image.getHeight() };
    RGB temp_rgb;
    for (int i = 0; i < new_intensity->getHeight()*new_intensity->getWidth(); i++){
        temp_rgb = image.getPixel(i);

#ifdef EFFICIENT_RGB_CONVERSION
        new_intensity->setPixel(i, (temp_rgb.r + temp_rgb.r + temp_rgb.g + temp_rgb.g + temp_rgb.g + temp_rgb.b) / 6);
#else
        new_intensity->setPixel(i, static_cast<unsigned char>(sqrt(0.299 * temp_rgb.r * temp_rgb.r + 0.587 * temp_rgb.g * temp_rgb.g + 0.114 * temp_rgb.b * temp_rgb.b)));
#endif
    }
    return new_intensity;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	return nullptr;
}