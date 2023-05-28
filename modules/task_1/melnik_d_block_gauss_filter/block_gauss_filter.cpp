// Copyright 2023 Melnik Denis
#include "../../../modules/task_1/melnik_d_block_gauss_filter/block_gauss_filter.h"

Image GaussFilter(const Image &origin) {
    double kernel[] = {0.0625, 0.125,  0.0625, 0.125, 0.25,
                       0.125,  0.0625, 0.125,  0.0625};

    Image result = origin;

    for (int y = 0; y < origin.H(); y++) {
        for (int x = 0; x < origin.W(); x++) {
            double pixel_res = 0;
            pixel_res += origin.GetPixel(x - 1, y - 1) * kernel[0];
            pixel_res += origin.GetPixel(x, y - 1) * kernel[1];
            pixel_res += origin.GetPixel(x + 1, y - 1) * kernel[2];

            pixel_res += origin.GetPixel(x - 1, y) * kernel[3];
            pixel_res += origin.GetPixel(x, y) * kernel[4];
            pixel_res += origin.GetPixel(x + 1, y) * kernel[5];

            pixel_res += origin.GetPixel(x - 1, y + 1) * kernel[6];
            pixel_res += origin.GetPixel(x, y + 1) * kernel[7];
            pixel_res += origin.GetPixel(x + 1, y + 1) * kernel[8];
            result.SetPixel(x, y, pixel_res);
        }
    }

    return result;
}

Image::Image(int w, int h) : width(w), height(h), pixels(w * h) {}

int Image::GetPixel(int x, int y) const {
    if (x < 0)
        x = 0;
    else if (x >= width)
        x = width - 1;

    if (y < 0)
        y = 0;
    else if (y >= height)
        y = height - 1;

    return pixels[y * width + x];
}

void Image::SetPixel(int x, int y, int value) {
    if (value < 0)
        value = 0;
    else if (value > 256)
        value = 256;
    pixels[y * width + x] = value;
}

void Image::Load(int *pixels) {
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            SetPixel(x, y, pixels[y * width + x]);
}

void Image::Print() const {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++)
            cout << GetPixel(x, y) << ' ';
        cout << '\n';
    }
}

bool Image::operator==(const Image &other) const {
    return width == other.width && height == other.height &&
           pixels == other.pixels;
}
