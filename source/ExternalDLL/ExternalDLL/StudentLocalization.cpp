#include "StudentLocalization.h"
#include "ImageIO.h"
#include "StudentKernel.h"

bool StudentLocalization::stepFindHead(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindNoseMouthAndChin(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindChinContours(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindNoseEndsAndEyes(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindExactEyes(const IntensityImage &image, FeatureMap &features) const {

	ImageIO::saveIntensityImage(image, ImageIO::getDebugFileName("input.png"));

	IntensityImageStudent copy(image);

	double** d_kern = new double*[3];
	for (int y = 0; y < 3; y++) {
		d_kern[y] = new double[3];
	}
	d_kern[0][0] = 0;
	d_kern[0][1] = 1;
	d_kern[0][2] = 0;
	d_kern[1][0] = 1;
	d_kern[1][1] = 0;
	d_kern[1][2] = 1;
	d_kern[2][0] = 0;
	d_kern[2][1] = 1;
	d_kern[2][2] = 0;

	//kernel[0][0] = 0.5;
	//kernel[0][1] = 1;
	//kernel[0][2] = 0.5;
	//kernel[1][0] = 1;
	//kernel[1][1] = -6;
	//kernel[1][2] = 1;
	//kernel[2][0] = 0.5;
	//kernel[2][1] = -1;
	//kernel[2][2] = 0.5;


	StudentKernel dilation = StudentKernel(d_kern, 3, 3, 0);
	IntensityImageStudent test2 = dilation.dilate(&copy);
	ImageIO::saveIntensityImage(test2, ImageIO::getDebugFileName("test_kernel.png"));
	return true;
}