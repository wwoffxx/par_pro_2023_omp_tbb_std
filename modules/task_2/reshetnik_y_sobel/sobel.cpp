// Copyright 2023 Reshetnik Yana
#include "../../../modules/task_2/reshetnik_y_sobel/sobel.h"

std::vector<int> Gx({-1, 0, 1, -2, 0, 2, -1, 0, 1});
std::vector<int> Gy({-1, -2, -1, 0, 0, 0, 1, 2, 1});

Image::Image(int _wdth, int _hgt) {
    if ((_wdth <= 0) || (_hgt <= 0)) throw "Size is incorrect";
    width = _wdth;
    height = _hgt;
    matrix.resize(_wdth * _hgt);
    for (int i = 0; i < _wdth * _hgt; i++) matrix[i] = 0;
}

Image::Image(const std::vector<int>& mat) {
    matrix.resize(mat.size());
    for (int i = 0; i < mat.size(); ++i) matrix[i] = mat[i];
}

Image getRandomImage(int _wdth, int _hgt) {
    if ((_wdth <= 0) || (_hgt <= 0)) throw "Size is incorrect";
    Image Ex1(_wdth, _hgt);
    std::mt19937 gen;
    for (int i = 0; i < _wdth; i++) {
        for (int j = 0; i < _hgt; i++) {
            Ex1.matrix[i * _wdth + j] = gen() % 256;
        }
    }
    return Ex1;
}

bool Image::EqualTo(const Image& img2) {
    if (this->height != img2.height || this->width != img2.width)
        throw "Unequal sizes";

    for (int i = 0; i < img2.width * img2.height; i++) {
        if (this->matrix[i] != img2.matrix[i]) return false;
    }

    return true;
}

Image SobelSeq(Image start) {
    if ((start.height <= 0) || (start.width <= 0) || (start.matrix.empty())) {
        throw "Image is incorrect";
    }

    Image result(start.width, start.height);

    int i = 0;
    while (i < start.width) {
        int j = 0;
        while (j < start.height) {
            int ind = i * start.height + j;
            int X = 0, Y = 0, Ind_G = 0;
            int a = 0, b = 0;
            while (a < 3) {
                while (b < 3) {
                    X = Gx[Ind_G] *
                            start.matrix[(i + a) * start.height + j + b] +
                        X;
                    Y = Gy[Ind_G] *
                            start.matrix[(i + a) * start.height + j + b] +
                        Y;
                    ++Ind_G;
                    ++b;
                }
                ++a;
            }
            if (sqrt(X * X + Y * Y) > 255) {
                result.matrix[ind] = 255;
            } else {
                result.matrix[ind] = sqrt(X * X + Y * Y);
            }
            ++j;
        }
        ++i;
    }
    return result;
}

Image SobelOMP(Image start) {
    if ((start.height <= 0) || (start.matrix.empty()) || (start.width <= 0))
        throw "Uncorrect Image";
    Image result(start.width, start.height);

#pragma omp parallel for
    for (int i = 0; i < start.width; ++i) {
        for (int j = 0; j < start.height; ++j) {
            int ind = i * start.height + j;
            int X = 0, Y = 0, Ind_G = 0;
            for (int a = 0; a < 3; ++a) {
                for (int b = 0; b < 3; ++b) {
                    X = Gx[Ind_G] *
                            start.matrix[(i + a) * start.height + j + b] +
                        X;
                    Y = Gy[Ind_G] *
                            start.matrix[(i + a) * start.height + j + b] +
                        Y;
                    Ind_G++;
                }
            }

            if (sqrt(X * X + Y * Y) > 255) {
                result.matrix[ind] = 255;
            } else {
                result.matrix[ind] = sqrt(X * X + Y * Y);
            }
        }
    }

    return result;
}
