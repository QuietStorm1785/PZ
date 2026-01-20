#pragma once
#include <vector>
#include <memory>
#include "BasicPixelProcessor.h"

namespace com {
namespace sixlegs {
namespace png {

class TransGammaPixelProcessor : public BasicPixelProcessor {
public:
   TransGammaPixelProcessor(std::shared_ptr<Destination> dst, const std::vector<short>& gammaTable, const std::vector<int>& trans, int shift, int samples, int sourceWidth)
      : BasicPixelProcessor(std::move(dst), samples), gammaTable(gammaTable), trans(trans), shift(shift), max(static_cast<int>(gammaTable.size()) - 1), samplesNoAlpha(this->samples - 1), temp(this->samples * sourceWidth) {}

   bool process(const std::vector<int>& pixels, int x, int xStep, int unused, int y, int count) override {
      int outLen = count * samplesNoAlpha;
      std::vector<int> out(outLen + count); // include alpha slot per pixel
      int srcIdx = 0;
      int dstIdx = 0;
      while (dstIdx < outLen) {
         bool anyNotTrans = false;
         for (int i = 0; i < samplesNoAlpha; ++i) {
            int val = pixels[srcIdx + i];
            anyNotTrans = anyNotTrans || (val != trans[i]);
            out[dstIdx + i] = static_cast<int>(0xFFFF & gammaTable[val >> shift]);
         }
         out[dstIdx + samplesNoAlpha] = anyNotTrans ? max : 0;
         srcIdx += samplesNoAlpha;
         dstIdx += this->samples;
      }

      return BasicPixelProcessor::process(out, x, xStep, unused, y, count);
   }

private:
   std::vector<short> gammaTable;
   std::vector<int> trans;
   int shift;
   int max;
   int samplesNoAlpha;
   std::vector<int> temp;
};

} // namespace png
} // namespace sixlegs
} // namespace com
