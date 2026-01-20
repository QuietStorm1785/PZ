#pragma once
#include <vector>
#include <memory>
#include <opencv2/core.hpp>
#include "PixelProcessor.h"
#include "Destination.h"

namespace com {
namespace sixlegs {
namespace png {

class BasicPixelProcessor : public PixelProcessor {
public:
   explicit BasicPixelProcessor(std::shared_ptr<Destination> dst, int samples)
      : dst_(std::move(dst)), samples(samples) {}

   bool process(const std::vector<int>& pixels, int x, int xStep, int /*unused*/, int y, int count) override {
      if (!dst_) return false;
      if (xStep == 1) {
         dst_->setPixels(x, y, count, pixels);
      } else {
         int px = x;
         size_t srcIndex = 0;
         size_t total = static_cast<size_t>(samples) * static_cast<size_t>(count);
         std::vector<int> sampleBuf(samples);
         while (srcIndex < total) {
            for (int s = 0; s < samples; ++s) sampleBuf[s] = pixels[srcIndex + s];
            dst_->setPixel(px, y, sampleBuf);
            px += xStep;
            srcIndex += samples;
         }
      }
      return true;
   }

   int samples;

private:
   std::shared_ptr<Destination> dst_;
};

} // namespace png
} // namespace sixlegs
} // namespace com
