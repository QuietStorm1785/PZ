#pragma once
#include <vector>
#include <memory>
#include <opencv2/core.hpp>
#include "Destination.h"

namespace com {
namespace sixlegs {
namespace png {

// Wraps a cv::Mat as a Destination. The cv::Mat is expected to be of type CV_32S
// with channel count equal to the number of samples per pixel.
class RasterDestination : public Destination {
public:
   RasterDestination(cv::Mat& mat, int sourceWidth) : mat_(mat), sourceWidth(sourceWidth) {}

   void setPixels(int x, int y, int count, const std::vector<int>& pixels) override {
      // pixels is samples*count in row-major; write sequential pixels starting at x
      int channels = mat_.channels();
      size_t idx = 0;
      for (int i = 0; i < count; ++i) {
         for (int c = 0; c < channels; ++c) {
            mat_.at<cv::Vec<int, 1>>(y, x + i)[0] = 0; // placeholder if single-channel
         }
         // Conservative implementation: set via setPixel per pixel
         std::vector<int> sample(channels);
         for (int c = 0; c < channels; ++c) {
            if (idx < pixels.size()) sample[c] = pixels[idx++];
         }
         setPixel(x + i, y, sample);
      }
   }

   void setPixel(int x, int y, const std::vector<int>& samples) override {
      int channels = mat_.channels();
      // write as int values into mat; if mat is not CV_32S, we will try to convert
      if (mat_.type() == CV_MAKETYPE(CV_32S, channels)) {
         for (int c = 0; c < std::min((int)samples.size(), channels); ++c) {
            if (channels == 1) {
               mat_.at<int>(y, x) = samples[c];
            } else {
               // For multi-channel, use Vec<int, N> via generic access
               // Use ptr to row
               int* rowPtr = mat_.ptr<int>(y) + x*channels;
               rowPtr[c] = samples[c];
            }
         }
      } else {
         // Fallback: convert sample to uchar and write into first channel
         for (int c = 0; c < std::min((int)samples.size(), channels); ++c) {
            mat_.at<cv::Vec<int,1>>(y, x)[0] = samples[c];
         }
      }
   }

   void getPixel(int x, int y, std::vector<int>& out) override {
      int channels = mat_.channels();
      out.resize(channels);
      if (mat_.type() == CV_MAKETYPE(CV_32S, channels)) {
         for (int c = 0; c < channels; ++c) {
            int* rowPtr = mat_.ptr<int>(y) + x*channels;
            out[c] = rowPtr[c];
         }
      } else {
         out[0] = mat_.at<int>(y, x);
      }
   }

   cv::Mat& getRaster() override { return mat_; }

   int getSourceWidth() const override { return sourceWidth; }

   void done() override {}

private:
   cv::Mat& mat_;
   int sourceWidth;
};

} // namespace png
} // namespace sixlegs
} // namespace com
