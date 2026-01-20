#pragma once
#include <vector>
#include <memory>
#include "BasicPixelProcessor.h"

namespace com {
namespace sixlegs {
namespace png {

class GammaPixelProcessor : public BasicPixelProcessor {
public:
   GammaPixelProcessor(std::shared_ptr<Destination> dst, const std::vector<short>& gammaTable, int shift, int samples)
      : BasicPixelProcessor(std::move(dst), samples), gammaTable(gammaTable), shift(shift) {
      hasAlpha = (this->samples % 2) == 0;
      samplesNoAlpha = hasAlpha ? this->samples - 1 : this->samples;
      shiftAlpha = hasAlpha && (shift > 0);
   }

   bool process(const std::vector<int>& pixels, int x, int xStep, int unused, int y, int count) override {
      // make a mutable copy
      std::vector<int> copy = pixels;
      int total = this->samples * count;
      for (int i = 0; i < samplesNoAlpha; ++i) {
         for (int idx = i; idx < total; idx += this->samples) {
            int v = copy[idx] >> shift;
            v = static_cast<int>(0xFFFF & gammaTable[v]);
            copy[idx] = v;
         }
      }

      if (shiftAlpha) {
         for (int idx = samplesNoAlpha; idx < total; idx += this->samples) {
            copy[idx] >>= shift;
         }
      }

      return BasicPixelProcessor::process(copy, x, xStep, unused, y, count);
   }

private:
   std::vector<short> gammaTable;
   int shift;
   int samplesNoAlpha;
   bool hasAlpha;
   bool shiftAlpha;
};

} // namespace png
} // namespace sixlegs
} // namespace com
