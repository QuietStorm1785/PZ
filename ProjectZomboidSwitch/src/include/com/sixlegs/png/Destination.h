#pragma once
#include <vector>
#include <cstdint>
#include <opencv2/core.hpp>

namespace com {
namespace sixlegs {
namespace png {

// Destination abstraction for decoded pixels. Implementations typically wrap an
// OpenCV matrix or other image storage.
class Destination {
public:
   // Set a run of pixels starting at (x,y). 'count' is number of pixels; 'pixels'
   // contains samples packed per-pixel (samples * count elements).
   virtual void setPixels(int x, int y, int count, const std::vector<int>& pixels) = 0;

   // Set a single pixel's samples at (x,y).
   virtual void setPixel(int x, int y, const std::vector<int>& samples) = 0;

   // Read a pixel's samples into 'out'.
   virtual void getPixel(int x, int y, std::vector<int>& out) = 0;

   // Return a reference to the underlying raster (cv::Mat).
   virtual cv::Mat& getRaster() = 0;

   virtual int getSourceWidth() const = 0;

   virtual void done() = 0;

   virtual ~Destination() = default;
};

} // namespace png
} // namespace sixlegs
} // namespace com
