#pragma once
#include <vector>
#include <memory>
#include <opencv2/core.hpp>
#include "Destination.h"

namespace com {
namespace sixlegs {
namespace png {

class SourceRegionDestination : public Destination {
public:
   SourceRegionDestination(std::shared_ptr<Destination> dst, const cv::Rect& region)
      : dst_(std::move(dst)), xoff(region.x), yoff(region.y), xlen(region.width), ylen(region.height), samples(dst_->getRaster().channels()) {}

   void setPixels(int x, int y, int count, const std::vector<int>& pixels) override {
      if (y >= yoff && y < yoff + ylen) {
         int start = std::max(x, xoff);
         int avail = std::min(x + count, xoff + xlen) - start;
         if (avail > 0) {
            std::vector<int> slice;
            if (start > x) {
               // copy the relevant range
               int startIdx = start - x;
               slice.resize(avail * samples);
               std::copy(pixels.begin() + startIdx * samples, pixels.begin() + (startIdx + avail) * samples, slice.begin());
            } else {
               slice = pixels;
            }
            dst_->setPixels(start - xoff, y - yoff, avail, slice);
         }
      }
   }

   void setPixel(int x, int y, const std::vector<int>& samplesVec) override {
      x -= xoff; y -= yoff;
      if (x >= 0 && y >= 0 && x < xlen && y < ylen) {
         dst_->setPixel(x, y, samplesVec);
      }
   }

   void getPixel(int x, int y, std::vector<int>& out) override {
      throw std::runtime_error("SourceRegionDestination::getPixel not supported");
   }

   cv::Mat& getRaster() override {
      return dst_->getRaster();
   }

   int getSourceWidth() const override { return dst_->getSourceWidth(); }

   void done() override { dst_->done(); }

private:
   std::shared_ptr<Destination> dst_;
   int xoff;
   int yoff;
   int xlen;
   int ylen;
   int samples;
};

} // namespace png
} // namespace sixlegs
} // namespace com
