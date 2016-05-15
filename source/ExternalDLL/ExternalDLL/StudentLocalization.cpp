#include "StudentLocalization.h"

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

	//StudentHistogram histo = ImageUtils::histogram_from_x_axis(&image, 140);
	//ImageIO::saveIntensityImage(*histo.get_debug_image(), ImageIO::getDebugFileName("histo.png"));

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

	StudentKernel dilation = StudentKernel(d_kern, 3, 3, 0);

	Feature top = features.getFeature(Feature::FEATURE_HEAD_TOP);
	Feature bottom = features.getFeature(Feature::FEATURE_CHIN);
	Feature headsideleft = features.getFeature(Feature::FEATURE_HEAD_LEFT_SIDE);
	Feature headsideright = features.getFeature(Feature::FEATURE_HEAD_RIGHT_SIDE);

	int head_height = bottom.getY() - top.getY();
	int head_width = headsideright.getX() - headsideleft.getX();

	Point2D<double> headsidelp = headsideleft.getPoints()[0];
	headsidelp.setY(headsidelp.getY() - (head_height / 4));
	headsidelp.setX(headsidelp.getX() + (head_width / 8));


	Point2D<double> headsiderp = headsideright.getPoints()[0];
	headsiderp.setX(headsiderp.getX() - (head_width / 8));

	Feature left = features.getFeature(Feature::FEATURE_EYE_LEFT_RECT);
	Feature right = features.getFeature(Feature::FEATURE_EYE_RIGHT_RECT);

	IntensityImageStudent eyes = ImageUtils::subimage(&image, headsidelp, headsiderp);
	IntensityImageStudent eyes_copy = dilation.dilate(&eyes);
	ImageIO::saveIntensityImage(eyes_copy, ImageIO::getDebugFileName("subimage_test.png"));

	StudentHistogram histo = ImageUtils::histogram_from_x_axis(&eyes_copy, 25);
	ImageIO::saveIntensityImage(*histo.get_debug_image(), ImageIO::getDebugFileName("histo.png"));

	left.addPoint(headsidelp);
	left.addPoint(headsidelp + Point2D<double>(head_width / 2, head_width/8));

	right.addPoint(headsidelp + Point2D<double>(head_width / 2, 0));
	right.addPoint(headsidelp + Point2D<double>(head_width / 2, head_width / 8));

	features.putFeature(left);
	features.putFeature(right);



	for (int y = 0; y < 3; y++) {
		delete[] d_kern[y];
	}
	delete[] d_kern;

	return true;
}