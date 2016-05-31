#include "StudentPreProcessing.h"


IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	return nullptr;
}
 
IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	IntensityImageStudent copy{ image } ;

	double** edge = new double*[9];
	for (int y = 0; y < 9; y++) {
		edge[y] = new double[9];
	}
	/*edge[0][0] = 0;
	edge[0][1] = 0;
	edge[0][2] = 0;
	edge[0][3] = 1;
	edge[0][4] = 1;
	edge[0][5] = 1;
	edge[0][6] = 0;
	edge[0][7] = 0;
	edge[0][8] = 0;

	edge[1][0] = 0;
	edge[1][1] = 0;
	edge[1][2] = 0;
	edge[1][3] = 1;
	edge[1][4] = 1;
	edge[1][5] = 1;
	edge[1][6] = 0;
	edge[1][7] = 0;
	edge[1][8] = 0;

	edge[2][0] = 0;
	edge[2][1] = 0;
	edge[2][2] = 0;
	edge[2][3] = 1;
	edge[2][4] = 1;
	edge[2][5] = 1;
	edge[2][6] = 0;
	edge[2][7] = 0;
	edge[2][8] = 0;

	edge[3][0] = 1;
	edge[3][1] = 1;
	edge[3][2] = 1;
	edge[3][3] = -4;
	edge[3][4] = -4;
	edge[3][5] = -4;
	edge[3][6] = 1;
	edge[3][7] = 1;
	edge[3][8] = 1;

	edge[4][0] = 1;
	edge[4][1] = 1;
	edge[4][2] = 1;
	edge[4][3] = -4;
	edge[4][4] = -4;
	edge[4][5] = -4;
	edge[4][6] = 1;
	edge[4][7] = 1;
	edge[4][8] = 1;

	edge[5][0] = 1;
	edge[5][1] = 1;
	edge[5][2] = 1;
	edge[5][3] = -4;
	edge[5][4] = -4;
	edge[5][5] = -4;
	edge[5][6] = 1;
	edge[5][7] = 1;
	edge[5][8] = 1;

	edge[6][0] = 0;
	edge[6][1] = 0;
	edge[6][2] = 0;
	edge[6][3] = 1;
	edge[6][4] = 1;
	edge[6][5] = 1;
	edge[6][6] = 0;
	edge[6][7] = 0;
	edge[6][8] = 0;

	edge[7][0] = 0;
	edge[7][1] = 0;
	edge[7][2] = 0;
	edge[7][3] = 1;
	edge[7][4] = 1;
	edge[7][5] = 1;
	edge[7][6] = 0;
	edge[7][7] = 0;
	edge[7][8] = 0;

	edge[8][0] = 0;
	edge[8][1] = 0;
	edge[8][2] = 0;
	edge[8][3] = 1;
	edge[8][4] = 1;
	edge[8][5] = 1;
	edge[8][6] = 0;
	edge[8][7] = 0;
	edge[8][8] = 0;*/

	edge[0][0] = -1;
	edge[0][1] = -1;
	edge[0][2] = -1;
	edge[1][0] = -1;
	edge[1][1] = 8;
	edge[1][2] = -1;
	edge[2][0] = -1;
	edge[2][1] = -1;
	edge[2][2] = -1;

	double** blur = new double*[3];
	for (int y = 0; y < 3; y++) {
		blur[y] = new double[3];
	}
	blur[0][0] = 1;
	blur[0][1] = 1;
	blur[0][2] = 1;
	blur[1][0] = 1;
	blur[1][1] = 1;
	blur[1][2] = 1;
	blur[2][0] = 1;
	blur[2][1] = 1;
	blur[2][2] = 1;

	double** dilate = new double*[3];
	for (int y = 0; y < 3; y++) {
		dilate[y] = new double[3];
	}
	dilate[0][0] = 0;
	dilate[0][1] = 1;
	dilate[0][2] = 0;
	dilate[1][0] = 1;
	dilate[1][1] = 1;
	dilate[1][2] = 1;
	dilate[2][0] = 0;
	dilate[2][1] = 1;
	dilate[2][2] = 0;

	StudentKernel dilation_k = StudentKernel(dilate, 3, 3, 0, 1);
	StudentKernel blur_k = StudentKernel(blur, 3, 3, 0, 0.11111111111111);
	StudentMedianFilter mf{};
	StudentKernel edge_k = StudentKernel(edge, 3, 3, 127, 1);
	IntensityImageStudent edges = blur_k.apply_on_image(&edge_k.apply_on_image(&blur_k.apply_on_image(&blur_k.apply_on_image(&copy))));
	ImageIO::saveIntensityImage(edges, ImageIO::getDebugFileName("edges.png"));

	IntensityImageStudent result_student = ImageUtils::zero_crossings(&edges);

	ImageIO::saveIntensityImage(result_student, ImageIO::getDebugFileName("result.png"));


	for (int y = 0; y < 9; y++) {
		delete[] edge[y];
	}
	delete[] edge;

	for (int y = 0; y < 3; y++) {
		delete[] blur[y];
	}
	delete[] blur;

	IntensityImage * result = ImageFactory::newIntensityImage(result_student);
	return result;

}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {

	return ImageFactory::newIntensityImage(ImageUtils::inverse(&ImageUtils::threshold(&image, 220)));
}