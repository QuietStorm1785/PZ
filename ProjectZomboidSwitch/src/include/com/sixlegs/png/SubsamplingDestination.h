#pragma once
#include <vector>
#include <memory>
#include "RasterDestination.h"

namespace com {
namespace sixlegs {
namespace png {

class SubsamplingDestination : public RasterDestination {
public:
   SubsamplingDestination(cv::Mat& mat, int sourceWidth, int xsub, int ysub, int xoff, int yoff)
      : RasterDestination(mat, sourceWidth), xsub(xsub), ysub(ysub), xoff(xoff), yoff(yoff), singlePixel(mat.channels()) {}

   void setPixels(int x, int y, int count, const std::vector<int>& pixels) override {
      if (((y - yoff) % ysub) == 0) {
         int px = (x - xoff) / xsub;
         int py = (y - yoff) / ysub;
         int startX = px * xsub + xoff;
         if (startX < x) {
            px++;
            startX += xsub;
         }
         int bands = getRaster().channels();
         int offset = startX - x;
         for (int pos = x + count; offset < pos; offset += xsub) {
            // copy single pixel (bands elements) from pixels at offset
            for (int b = 0; b < bands; ++b) {
               singlePixel[b] = pixels[offset * bands + b];
            }
            RasterDestination::setPixel(px++, py, singlePixel);
         }
      }
   }

   void setPixel(int x, int y, const std::vector<int>& samples) override {
      x -= xoff; y -= yoff;
      if (x % xsub == 0 && y % ysub == 0) {
         RasterDestination::setPixel(x / xsub, y / ysub, samples);
      }
   }

   void getPixel(int x, int y, std::vector<int>& out) override {
      throw std::runtime_error("SubsamplingDestination::getPixel not supported");
   }

private:
   int xsub;
   int ysub;
   int xoff;
   int yoff;
   std::vector<int> singlePixel;
};

} // namespace png
} // namespace sixlegs
} // namespace com
