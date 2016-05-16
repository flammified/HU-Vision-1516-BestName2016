#pragma once
#include <memory>
#include <iostream>
#include "StudentKernel.h"
IntensityImageStudent StudentKernel::apply_on_image(IntensityImage * img) {
	IntensityImageStudent temp_img{ *img };
	for (int y = 0; y < img->getHeight(); y++) {
		for (int x = 0; x < img->getWidth(); x++) {

			int temp = 0;

			for (int y_k = 0; y_k < this->h; y_k++) {
				for (int x_k = 0; x_k < this->w; x_k++) {
				
					int dx = x_k - 1;
					int dy = y_k - 1;

					Intensity pix_val = img->getPixel(x + dx, y + dy);
					
					temp += (pix_val * values[y_k][x_k]);
				}
			}
			temp = temp * factor + shift;
		
			temp_img.setPixel(x, y, temp);
		}
	}
	return temp_img; 
}

IntensityImageStudent StudentKernel::dilate(IntensityImage * img) {
	IntensityImageStudent temp_img{ *img };


	for (int y = 0; y < img->getHeight(); y++) {
		for (int x = 0; x < img->getWidth(); x++) {
			
			if (img->getPixel(x, y) == 0) {

				for (int y_k = 0; y_k < this->h; y_k++) {
					for (int x_k = 0; x_k < this->w; x_k++) {

						int dx = x_k - 1;
						int dy = y_k - 1;
						if (values[y_k][x_k] > 0) {
							temp_img.setPixel(x + dx, y + dy, 0);
						}
					}
				}
			}
		
		}
	}
	return temp_img;
}