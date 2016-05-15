#include "StudentMedianFilter.h"

IntensityImage * StudentMedianFilter::apply_on_image(const IntensityImage &img){
    IntensityImage * new_img = new IntensityImageStudent{img.getWidth(), img.getHeight()};
    for (int row = 0; row < img.getHeight(); row++){/*
        for (int i = 0; i < filterSize; i++){
            for (int j = 0; j < filterSize; j++){
                sort[filterSize*i + j] = img.getPixel(i -filterSize/2, j + row -filterSize/2);
            }
        }*/

        for (int p = 0; p < img.getWidth(); p++){
            for (int i = 0; i < filterSize; i++){
                for (int j = 0; j < filterSize; j++){
                    sort[filterSize*i + j] = img.getPixel(p + (i - filterSize / 2), j + row - filterSize / 2);
                }
            }

            new_img->setPixel(p, row, Intensity{ findQuickMedian() });
            /*
            char * newVal = new char[filterSize];
            char * oldVal = new char[filterSize];
            bool * found = new bool[filterSize];
            int newValIt = 0;
            for (int i = 0; i < filterSize; i++){
                newVal[i] = img.getPixel(p + 2, row + i - filterSize / 2);
                oldVal[i] = img.getPixel(p - 1, row + i - filterSize / 2);
                found[i] = false;
            }
            for (int i = 0; i < filterSize * filterSize && newValIt < filterSize; i++){
                for (int j = 0; j < filterSize; j++){
                    if (oldVal[j] == sort[i] && !found[j]){
                        sort[i] = newVal[newValIt++];
                        found[j] = true;
                    }
                }
            }
            */
        }
    }
    return new_img;
}

StudentMedianFilter::StudentMedianFilter(int filterSize) :
    filterSize{filterSize}
{
    sort = new unsigned char[filterSize * filterSize];
}


StudentMedianFilter::~StudentMedianFilter()
{
    delete[] sort;
}

unsigned char StudentMedianFilter::findQuickMedian(){
    int L = 0;
    int R = (filterSize * filterSize) - 1;
    int i, j;
    unsigned char x;
    while (L < R){
        x = sort[(filterSize * filterSize) / 2];
        i = L;
        j = R;
        do{
            while (sort[i] < x) i++;
            while (sort[j] > x) j--;
            if (i <= j){
                unsigned char t = sort[i];
                sort[i] = sort[j];
                sort[j] = t;
                i++; j--;
            }
        } while (i <= j);
        if (j < (filterSize * filterSize) / 2) L = i;
        if ((filterSize * filterSize) / 2 < i) R = j;
    }
    return x;
}