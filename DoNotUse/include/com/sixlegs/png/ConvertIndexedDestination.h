#pragma once
#include <vector>
#include <memory>
#include "Destination.h"
#include "IndexColorModel.h"

namespace com {
namespace sixlegs {
namespace png {

class ConvertIndexedDestination : public Destination {
public:
   ConvertIndexedDestination(std::shared_ptr<Destination> dst, int width, std::shared_ptr<IndexColorModel> srcColorModel, int dstSamples)
      : dst_(std::move(dst)), srcColorModel_(std::move(srcColorModel)), srcSamples(srcColorModel_->getNumComponents()), dstSamples(dstSamples), sampleDiff(srcSamples - dstSamples), row(width * dstSamples + sampleDiff) {}

   void setPixels(int x, int y, int count, const std::vector<int>& indices) override {
      int idx = count - 1;
      int outPos = dstSamples * idx;
      for (; idx >= 0; --idx, outPos -= dstSamples) {
         srcColorModel_->getComponents(indices[idx], row, outPos);
      }
      if (sampleDiff != 0) {
         // shift array left by sampleDiff
         std::copy(row.begin() + sampleDiff, row.begin() + sampleDiff + dstSamples * count, row.begin());
      }
      dst_->setPixels(x, y, count, row);
   }

   void setPixel(int x, int y, const std::vector<int>& samplesVec) override {
      setPixels(x, y, 1, samplesVec);
   }

   void getPixel(int x, int y, std::vector<int>& out) override {
      throw std::runtime_error("ConvertIndexedDestination::getPixel not implemented");
   }

   cv::Mat& getRaster() override { return dst_->getRaster(); }

   int getSourceWidth() const override { return dst_->getSourceWidth(); }

   void done() override { dst_->done(); }

private:
   std::shared_ptr<Destination> dst_;
   std::shared_ptr<IndexColorModel> srcColorModel_;
   int srcSamples;
   int dstSamples;
   int sampleDiff;
   std::vector<int> row;
};

} // namespace png
} // namespace sixlegs
} // namespace com
