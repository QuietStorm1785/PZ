#pragma once
#include "java/awt/image/WritableRaster.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace com {
namespace sixlegs {
namespace png {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SubsamplingDestination : public RasterDestination {
public:
  const int xsub;
  const int ysub;
  const int xoff;
  const int yoff;
private
  final int[] singlePixel;

public
  SubsamplingDestination(WritableRaster writableRaster, int int0, int int1,
                         int int2, int int3, int int4) {
    super(writableRaster, int0);
    this.xsub = int1;
    this.ysub = int2;
    this.xoff = int3;
    this.yoff = int4;
    this.singlePixel = new int[writableRaster.getNumBands()];
  }

  void setPixels(int int2, int int0, int int8, int[] ints) {
    if ((int0 - this.yoff) % this.ysub == 0) {
      int int1 = (int2 - this.xoff) / this.xsub;
      int int3 = (int0 - this.yoff) / this.ysub;
      int int4 = int1 * this.xsub + this.xoff;
      if (int4 < int2) {
        int1++;
        int4 += this.xsub;
      }

      int int5 = this.raster.getNumBands();
      int int6 = int4 - int2;

      for (int int7 = int2 + int8; int6 < int7; int6 += this.xsub) {
        System.arraycopy(ints, int6 * int5, this.singlePixel, 0, int5);
        super.setPixel(int1++, int3, this.singlePixel);
      }
    }
  }

  void setPixel(int int0, int int1, int[] ints) {
    int0 -= this.xoff;
    int1 -= this.yoff;
    if (int0 % this.xsub == 0 && int1 % this.ysub == 0) {
      super.setPixel(int0 / this.xsub, int1 / this.ysub, ints);
    }
  }

  void getPixel(int var1, int var2, int[] var3) {
    throw std::make_unique<UnsupportedOperationException>();
  }
}
} // namespace png
} // namespace sixlegs
} // namespace com
