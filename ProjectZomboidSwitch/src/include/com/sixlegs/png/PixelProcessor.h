#pragma once
#include <vector>
#include <cstdint>

namespace com {
namespace sixlegs {
namespace png {

// Abstract interface for pixel processors used by the PNG decoding pipeline.
// The parameter order follows the original implementation: pixels, x, xStep, unused, y, count
class PixelProcessor {
public:
   // pixels: packed integer samples
   // x: starting x coordinate
   // xStep: horizontal step between pixels (1 for contiguous)
   // unused: reserved (keeps parity with original signatures)
   // y: y coordinate
   // count: number of pixels (or scanline sample groups)
   virtual bool process(const std::vector<int>& pixels, int x, int xStep, int /*unused*/, int y, int count) = 0;
   virtual ~PixelProcessor() = default;
};

} // namespace png
} // namespace sixlegs
} // namespace com
