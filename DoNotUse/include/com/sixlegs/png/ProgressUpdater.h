#pragma once
#include <vector>
#include <memory>
#include <opencv2/core.hpp>
#include "PixelProcessor.h"

namespace com {
namespace sixlegs {
namespace png {

class PngImage; // forward

class ProgressUpdater : public PixelProcessor {
public:
   static constexpr int STEP_PERCENT = 5;
   ProgressUpdater(PngImage& png, cv::Mat& image, std::shared_ptr<PixelProcessor> pp)
      : png_(png), image_(image), pp_(std::move(pp)), total(png.getWidth() * png.getHeight()), step(std::max(1, total * STEP_PERCENT / 100)), count(0), mod(0) {}

   bool process(const std::vector<int>& pixels, int x, int xStep, int unused, int y, int countPixels) override {
      bool ok = pp_ ? pp_->process(pixels, x, xStep, unused, y, countPixels) : true;
      mod += countPixels;
      count += countPixels;
      if (mod > step) {
         mod = mod % step;
         ok = ok && png_.handleProgress(image_, 100.0f * float(count) / float(total));
      }
      return ok;
   }

private:
   PngImage& png_;
   cv::Mat& image_;
   std::shared_ptr<PixelProcessor> pp_;
   int total;
   int step;
   int count;
   int mod;
};

} // namespace png
} // namespace sixlegs
} // namespace com
