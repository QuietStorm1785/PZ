#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/awt/Rectangle.h"
#include "java/awt/image/WritableRaster.h"

namespace com {
namespace sixlegs {
namespace png {


class SourceRegionDestination :  Destination {
:
    const Destination dst;
    const int xoff;
    const int yoff;
    const int xlen;
    const int ylen;
    const int samples;

     SourceRegionDestination(Destination var1, Rectangle var2) {
      this.dst = var1;
      this.xoff = var2.x;
      this.yoff = var2.y;
      this.xlen = var2.width;
      this.ylen = var2.height;
      this.samples = var1.getRaster().getNumBands();
   }

    void setPixels(int var1, int var2, int var3, int[] var4) {
      if (var2 >= this.yoff && var2 < this.yoff + this.ylen) {
    int var5 = Math.max(var1, this.xoff);
    int var6 = Math.min(var1 + var3, this.xoff + this.xlen) - var5;
         if (var6 > 0) {
            if (var5 > var1) {
               System.arraycopy(var4, var5 * this.samples, var4, 0, var6 * this.samples);
            }

            this.dst.setPixels(var5 - this.xoff, var2 - this.yoff, var6, var4);
         }
      }
   }

    void setPixel(int var1, int var2, int[] var3) {
      var1 -= this.xoff;
      var2 -= this.yoff;
      if (var1 >= 0 && var2 >= 0 && var1 < this.xlen && var2 < this.ylen) {
         this.dst.setPixel(var1, var2, var3);
      }
   }

    void getPixel(int var1, int var2, int[] var3) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    WritableRaster getRaster() const {
      return this.dst.getRaster();
   }

    int getSourceWidth() const {
      return this.dst.getSourceWidth();
   }

    void done() {
      this.dst.done();
   }
}
} // namespace png
} // namespace sixlegs
} // namespace com
