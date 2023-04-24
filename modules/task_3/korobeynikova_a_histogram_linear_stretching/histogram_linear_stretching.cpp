// Copyright 2023 Korobeynikova Alice
#include "../../../modules/task_3/korobeynikova_a_histogram_linear_stretching/histogram_linear_stretching.h"

#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <tbb/parallel_reduce.h>
#include <tbb/task_arena.h>

#include <iostream>

constexpr int RANGEMIN = 0;
constexpr int RANGEMAX = 255;

static std::pair<Color, Color> parFindRange(const Image& image) {
  auto range = std::make_pair(Color(RANGEMAX), Color(RANGEMIN));
  return tbb::parallel_reduce(
      tbb::blocked_range<Image::const_iterator>(
          image.begin(), image.end()),  // range for searching min & max
      std::make_pair(Color(RANGEMAX), Color(RANGEMIN)),  // start value
      [&image](const tbb::blocked_range<Image::const_iterator>&
                   range,  // operator() implementation
               std::pair<Color, Color> min_max) {
        for (auto pixel : range) {
          min_max.first = std::min(min_max.first, pixel);
          min_max.second = std::max(min_max.second, pixel);
        }
        return min_max;
      },
      [](std::pair<Color, Color> min_max1,  // join() implementation
         std::pair<Color, Color> min_max2) -> std::pair<Color, Color> {
        return std::make_pair(std::min(min_max1.first, min_max2.first),
                              std::max(min_max1.second, min_max2.second));
      });
}

static std::pair<Color, Color> seqFindRange(const Image& image) {
  std::pair<Color, Color> range({RANGEMAX, RANGEMIN});
  for (int i = 0; i < image.size(); ++i) {
    range.first = std::min(image[i], range.first);
    range.second = std::max(image[i], range.second);
  }
  return range;
}

void sequentialLinearHistogramStretching(Image* image_ptr) {
  Image& image = *image_ptr;
  std::pair<Color, Color> range = seqFindRange(image);
  if (range.second != range.first) {
    for (auto& pixel : image) {
      pixel = (pixel - range.first) * (RANGEMAX - RANGEMIN) /
              (range.second - range.first);
    }
  }
}

void parallelLinearHistogramStretching(Image* image_ptr) {
  Image& image = *image_ptr;
  std::pair<Color, Color> min_max = parFindRange(image);
  if (min_max.second != min_max.first) {
    tbb::parallel_for(
        tbb::blocked_range<size_t>(0, image.size()),
        [&image, min_max](tbb::blocked_range<size_t> range) {
          for (auto i = range.begin(); i < range.end(); ++i) {
            image[i] = (image[i] - min_max.first) * (RANGEMAX - RANGEMIN) /
                       (min_max.second - min_max.first);
          }
        });
  }
}
