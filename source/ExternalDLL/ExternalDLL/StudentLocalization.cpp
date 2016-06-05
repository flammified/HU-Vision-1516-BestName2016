#include "StudentLocalization.h"
//#define DEBUG
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

   int temp = 0;
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

	StudentKernel dilation = StudentKernel(d_kern, 3, 3, 0);

   Feature top = features.getFeature(Feature::FEATURE_HEAD_TOP);
   Feature bottom = features.getFeature(Feature::FEATURE_CHIN);
	Feature nose_bottom = features.getFeature(Feature::FEATURE_NOSE_BOTTOM);
	Feature headsideleft = features.getFeature(Feature::FEATURE_HEAD_LEFT_SIDE);
	Feature headsideright = features.getFeature(Feature::FEATURE_HEAD_RIGHT_SIDE);

   const int nose_to_top = nose_bottom.getY() - top.getY();

#if UNNECESSARY_CODE
#endif
	Point2D<double> headsidelp = headsideleft.getPoints()[0];
	headsidelp.setY(top.getY() + (nose_to_top*3/5));
	headsidelp.setX((headsidelp.getX()));


	Point2D<double> headsiderp = headsideright.getPoints()[0];
   headsiderp.setY(nose_bottom.getY() - (nose_to_top*1/5));
	headsiderp.setX((headsiderp.getX() + 3));


   IntensityImageStudent eyes = ImageUtils::subimage(&image, headsidelp, headsiderp);
	IntensityImageStudent eyes_dilated = dilation.dilate(&eyes);

   StudentHistogram histo{eyes_dilated.getWidth()};
   int zero_points[2] = { 0, histo.get_length() * 1 / 7 };
   int lowest_found[2] = { eyes_dilated.getHeight(), eyes_dilated.getHeight() };

   int left_out = 0, left_out_x = 0,
       right_out = 0, right_out_x = 0,
       left_in = 0, left_in_x = 0,
       right_in = 0, right_in_x = 0;

   for (int x = 0; x < histo.get_length(); x++){
       temp = 0;
       for (int y = 0; y < eyes_dilated.getHeight(); y++){
           temp += eyes_dilated.getPixel(x, y) > 127 ? 0 : 1;
       }
       histo.set_value(x, temp);
       if (x < histo.get_length() * 3 / 10 && temp <= lowest_found[0]){
           lowest_found[0] = temp;
           zero_points[0] = x;
       }
       if (x > histo.get_length() * 7 / 10 && temp < lowest_found[1]){
           lowest_found[1] = temp;
           zero_points[1] = x;
       }
   }

   headsidelp.setX(headsidelp.getX() + zero_points[0]);
   headsiderp.setX(headsiderp.getX() - (histo.get_length() - zero_points[1]));

   headsidelp.setY(top.getY() + (nose_to_top * 2/ 5));
   headsiderp.setY(nose_bottom.getY());

   IntensityImageStudent eyes2(ImageUtils::subimage(&image, headsidelp, headsiderp));
   IntensityImageStudent eyes_copy2(dilation.dilate(&eyes2));

   histo.cut_to_size(zero_points[0], zero_points[1]);
   for (int x = 0; x < histo.get_length(); x++){
       if (x < histo.get_length() * 2 / 9){
           left_out_x = histo.get_value(x) > left_out ? x : left_out_x;
           left_out = histo.get_value(x) > left_out ? histo.get_value(x) : left_out;
       }
       else if (x < histo.get_length() * 4 / 9 && x > histo.get_length() * 2 / 9){
           left_in_x = histo.get_value(x) > left_in ? x : left_in_x;
           left_in = histo.get_value(x) > left_in ? histo.get_value(x) : left_in;
       }
       else if (x > histo.get_length() * 7 / 9){
           right_out_x = histo.get_value(x) > right_out ? x : right_out_x;
           right_out = histo.get_value(x) > right_out ? histo.get_value(x) : right_out;
       }
       else if (x > histo.get_length() * 5 / 9){
           right_in_x = histo.get_value(x) > right_in ? x : right_in_x;
           right_in = histo.get_value(x) > right_in ? histo.get_value(x) : right_in;
       }
   }

   int forehead_val = 10, forehead_y = 0;
   StudentHistogram histo2{eyes_copy2.getHeight()};
   for (int y = 0; y < histo2.get_length(); y++){
       temp = 0;
       for (int x = 0; x < eyes_copy2.getWidth(); x++){
           temp += eyes_copy2.getPixel(x, y) > 127 ? 0 : 1;
       }
       histo2.set_value(y, temp);
   }
   for (int y = 0; y < histo2.get_length(); y++){
       if (histo2.get_value(y) <= forehead_val){
           forehead_val = histo2.get_value(y);
           forehead_y = y;
       }
       else if (histo2.get_value(y) > 35 && forehead_val != 10) break;
   }

   headsidelp.setY(top.getY() + (nose_to_top * 2 / 5) + forehead_y);
   forehead_val = 15, forehead_y = histo2.get_length() -1;

   for (int y = histo2.get_length() -1; y > 0; --y){
       if (histo2.get_value(y) <= forehead_val){
           forehead_val = histo2.get_value(y);
           forehead_y = y;
       }
       else if (histo2.get_value(y) > 40 && forehead_val != 15) break;
   }

   headsiderp.setY(nose_bottom.getY() - (histo2.get_length() - forehead_y + 4));

   Point2D<double> precise_ref{headsidelp};
   IntensityImageStudent eyes3(ImageUtils::subimage(&image, headsidelp, headsiderp));
   IntensityImageStudent eyes_copy3(dilation.dilate(&eyes3));

#ifdef DEBUG
   ImageIO::saveIntensityImage(eyes2, ImageIO::getDebugFileName("first eye cut.png"));
   ImageIO::saveIntensityImage(eyes_copy3, ImageIO::getDebugFileName("subimage_test3.png"));
#endif // DEBUG

   StudentHistogram histo4{ eyes_copy3.getHeight() };
   for (int y = 0; y < histo4.get_length(); y++){
       temp = 0;
       for (int x = 0; x < eyes_copy3.getWidth(); x++){
           temp += eyes_copy3.getPixel(x, y) > 127 ? 0 : 1;
       }
       histo4.set_value(y, temp);
   }

#ifdef DEBUG
   ImageIO::saveIntensityImage(*histo2.get_debug_image(), ImageIO::getDebugFileName("histo2.png"));
#endif // DEBUG

   int step = 0, bottom_eye_y = headsiderp.getY(), top_eye_y = headsidelp.getY() +10;
   for (int y = histo4.get_length(); y > 0; --y){
       if (step == 0 && histo4.get_value(y) > 30){ bottom_eye_y = y; step++; }
       if (step == 1 && histo4.get_value(y) < histo4.get_value(bottom_eye_y)){
           top_eye_y = y;
           break;
       }
   }

   IntensityImageStudent eyes_precise{eyes3};
   for (int x = 0; x < eyes_precise.getWidth(); x++){ eyes_precise.setPixel(x, top_eye_y, 127); eyes_precise.setPixel(x, bottom_eye_y + 2, 127); }
   for (int y = 0; y < eyes_precise.getHeight(); y++){
       eyes_precise.setPixel(left_in_x, y, 127);
       eyes_precise.setPixel(right_in_x, y, 127);
       eyes_precise.setPixel(left_out_x, y, 127);
       eyes_precise.setPixel(right_out_x, y, 127);
   }
   bottom_eye_y += 2;
   IntensityImageStudent eyes_precise2 = ImageUtils::subimage( &eyes_precise, Point2D<double>{0.0, (double)(top_eye_y)}, Point2D<double>{(double)eyes_precise.getWidth(), (double)bottom_eye_y} );

#ifdef DEBUG
   ImageIO::saveIntensityImage(eyes_precise2, ImageIO::getDebugFileName("eyes_precise.png"));
   ImageIO::saveIntensityImage(*histo.get_debug_image(), ImageIO::getDebugFileName("histo.png"));

#endif // DEBUG

   StudentHistogram histoTopBottom{eyes_precise2.getWidth()};
   for (int i = 0; i < histoTopBottom.get_length(); i++){
       temp = 0;
       for (int j = 0; j < eyes_precise2.getHeight(); j++){
           temp += eyes_precise2.getPixel(i, j) > 127? 0: 1;
       }
       histoTopBottom.set_value(i, temp);
   }

#ifdef DEBUG
   ImageIO::saveIntensityImage(*histoTopBottom.get_debug_image(), ImageIO::getDebugFileName("histo.png"));
#endif // DEBUG

   int outsideLeftX = 0, insideLeftX = 0, insideRightX = 0, outsideRightX = histoTopBottom.get_length()-1;
   for (int i = 0; i < histoTopBottom.get_length(); i++){
       if (histoTopBottom.get_value(i) > eyes_precise2.getHeight() / 2 && i < histoTopBottom.get_length()*1/4){
           outsideLeftX = i;
           i = histoTopBottom.get_length() * 1 / 4;
       }
       else if (histoTopBottom.get_value(i) < eyes_precise2.getHeight() / 3 && i < histoTopBottom.get_length() / 2 && i > histoTopBottom.get_length() * 1 / 4){
           insideLeftX = i;
           i = histoTopBottom.get_length() / 2;
       }
       else if (histoTopBottom.get_value(i) > eyes_precise2.getHeight() / 2 && i < histoTopBottom.get_length() * 3 / 4 && i > histoTopBottom.get_length() / 2){
           insideRightX = i;
           i = histoTopBottom.get_length() * 3 / 4;
       }
       else if (histoTopBottom.get_value(i) < eyes_precise2.getHeight() / 3 && i > histoTopBottom.get_length() * 3 / 4){
           outsideRightX = i;
           break;
       }
   }

#ifdef DEBUG
   IntensityImageStudent eyes_precise21 = ImageUtils::subimage(&eyes_precise, Point2D<double>{(double)outsideLeftX, (double)(top_eye_y)}, Point2D<double>{(double)insideLeftX, (double)bottom_eye_y});
   ImageIO::saveIntensityImage(eyes_precise21, ImageIO::getDebugFileName("left_eye.png"));


   IntensityImageStudent eyes_precise22 = ImageUtils::subimage(&eyes_precise, Point2D<double>{(double)insideRightX, (double)(top_eye_y)}, Point2D<double>{(double)outsideRightX, (double)bottom_eye_y});
   ImageIO::saveIntensityImage(eyes_precise22, ImageIO::getDebugFileName("right_eye.png"));
#endif

   Feature left = Feature(Feature::FEATURE_EYE_LEFT_RECT);
   Feature right = Feature(Feature::FEATURE_EYE_RIGHT_RECT);

   left.addPoint(precise_ref + Point2D<double>{(double)outsideLeftX, (double)(top_eye_y)});
   left.addPoint(precise_ref + Point2D<double>{(double)insideLeftX, (double)bottom_eye_y});

   right.addPoint(precise_ref + Point2D<double>{(double)insideRightX, (double)(top_eye_y)});
   right.addPoint(precise_ref + Point2D<double>{(double)outsideRightX, (double)bottom_eye_y});

	features.putFeature(right);
	features.putFeature(left);


	for (int y = 0; y < 3; y++) {
		delete[] d_kern[y];
	}
	delete[] d_kern;

	return true;
}