#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "PixelProcessor.h"
#include "Destination.h"

namespace com {
namespace sixlegs {
namespace png {

class ProgressivePixelProcessor : public PixelProcessor {
public:
   ProgressivePixelProcessor(std::shared_ptr<Destination> dst, std::shared_ptr<PixelProcessor> pp, int imgWidth, int imgHeight)
      : pp_(std::move(pp)), imgWidth(imgWidth), imgHeight(imgHeight), dst_(std::move(dst)), samples( (dst_ ? dst_->getRaster().channels() : 1) ), pixels(samples * 8) {}

   bool process(const std::vector<int>& pixelsIn, int x, int xStep, int unused, int y, int count) override {
      if (pp_) pp_->process(pixelsIn, x, xStep, unused, y, count);
      int step = xStep - x;
      if (step > 1 || xStep > 1) {
         int yLimit = std::min(y + xStep, imgHeight);
         int idx = 0;
         int curX = x;
         while (idx < count) {
            // read existing pixel at (curX,y)
            dst_->getPixel(curX, y, pixels);
            int fillTo = std::min(curX + step, imgWidth);
            int span = fillTo - curX;
            // replicate last sample values to fill span
            for (int s = samples; s < span * samples; ++s) {
               pixels[s] = pixels[s - samples];
            }
            for (int yy = y; yy < yLimit; ++yy) {
               dst_->setPixels(curX, yy, span, pixels);
            }
            curX += xStep;
            ++idx;
         }
      }
      return true;
   }

private:
   std::shared_ptr<PixelProcessor> pp_;
   int imgWidth;
   int imgHeight;
   std::shared_ptr<Destination> dst_;
   int samples;
   std::vector<int> pixels;
};

} // namespace png
} // namespace sixlegs
} // namespace com
