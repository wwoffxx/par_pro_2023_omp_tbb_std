// Copyright 2023 Melnik Denis
#include "../../../modules/task_2/melnik_d_block_gauss_filter/block_gauss_filter.h"

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

Image GaussFilterBlockParallel(const Image &origin) {
    Image result = Image(origin.W(), origin.H());

    vector<GaussBlock> blocks = origin.GetBlocks();

#pragma omp parallel for
    for (int i = 0; i < blocks.size(); i++) {
        int y = i / origin.W();
        int x = i % origin.W();
        result.SetPixel(x, y, blocks[i].GaussValue());
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

void Image::FillRandom() {
    std::random_device dev;
    std::mt19937 gen(dev());

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int value = gen() % 256;
            SetPixel(x, y, value);
        }
    }
}

void Image::Load(int *pixels) {
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            SetPixel(x, y, pixels[y * width + x]);
}

void Image::Print() const {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++)
            cout << GetPixel(x, y) << "\t";
        cout << '\n';
    }
}

bool Image::operator==(const Image &other) const {
    return width == other.width && height == other.height &&
           pixels == other.pixels;
}

vector<GaussBlock> Image::GetBlocks() const {
    vector<GaussBlock> list;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            GaussBlock block;

            block.pixels[0][0] = GetPixel(x - 1, y - 1);
            block.pixels[1][0] = GetPixel(x, y - 1);
            block.pixels[2][0] = GetPixel(x + 1, y - 1);

            block.pixels[0][1] = GetPixel(x - 1, y);
            block.pixels[1][1] = GetPixel(x, y);
            block.pixels[2][1] = GetPixel(x + 1, y);

            block.pixels[0][2] = GetPixel(x - 1, y + 1);
            block.pixels[1][2] = GetPixel(x, y + 1);
            block.pixels[2][2] = GetPixel(x + 1, y + 1);

            list.push_back(block);
        }
    }
    return list;
}

int GaussBlock::GaussValue() {
    double kernel[] = {0.0625, 0.125,  0.0625, 0.125, 0.25,
                       0.125,  0.0625, 0.125,  0.0625};

    double pixel_res = 0;
    pixel_res += pixels[0][0] * kernel[0];
    pixel_res += pixels[1][0] * kernel[1];
    pixel_res += pixels[2][0] * kernel[2];

    pixel_res += pixels[0][1] * kernel[3];
    pixel_res += pixels[1][1] * kernel[4];
    pixel_res += pixels[2][1] * kernel[5];

    pixel_res += pixels[0][2] * kernel[6];
    pixel_res += pixels[1][2] * kernel[7];
    pixel_res += pixels[2][2] * kernel[8];

    return pixel_res;
}

void GaussBlock::Print() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << pixels[j][i] << " ";
        }
        cout << "\n";
    }
}
