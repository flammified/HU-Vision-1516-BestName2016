#pragma once
#include "IntensityImageStudent.h"

class StudentMedianFilter
{
public:
    StudentMedianFilter(int filterSize = 3);
    ~StudentMedianFilter();

    IntensityImage * apply_on_image(const IntensityImage &img);
private:
    unsigned char * sort;
    int filterSize;
    unsigned char findQuickMedian();
};

