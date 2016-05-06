#pragma once
#include <memory>
#include "StudentKernel.h"
IntensityImageStudent StudentKernel::apply_on_image(IntensityImageStudent img) {
	for (int y = 0; y < img.getHeight(); y++) {
		for (int x = 0; x < img.getWidth(); x++) {

			int temp = 0;

			for (int y_k = 0; y_k < this->h; y_k++) {
				for (int x_k = 0; x_k < this->w; x_k++) {
				
					int dx = x_k - 1;
					int dy = y_k - 1;

					Intensity pix_val = img.getPixel(x + x_k + dx, y + y_k + dy);
					
					temp += (pix_val * values[y_k][x_k]);
				}
			}

			img.setPixel(x, y, temp * factor);
		}
	}
	return img;
}