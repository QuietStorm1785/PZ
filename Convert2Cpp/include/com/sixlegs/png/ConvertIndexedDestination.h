#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/awt/image/ComponentColorModel.h"
#include "java/awt/image/IndexColorModel.h"
#include "java/awt/image/WritableRaster.h"

namespace com {
namespace sixlegs {
namespace png {


class ConvertIndexedDestination : public Destination {
public:
    const Destination dst;
    const IndexColorModel srcColorModel;
    const int srcSamples;
    const int dstSamples;
    const int sampleDiff;
   private final int[] row;

    public ConvertIndexedDestination(Destination var1, int var2, IndexColorModel var3, ComponentColorModel var4) {
      this.dst = var1;
      this.srcColorModel = var3;
      this.srcSamples = var3.getNumComponents();
      this.dstSamples = var4.getNumComponents();
      this.sampleDiff = this.srcSamples - this.dstSamples;
      this.row = new int[var2 * this.dstSamples + this.sampleDiff];
   }

    void setPixels(int var1, int var2, int var3, int[] var4) {
    int var5 = var3 - 1;

      for (int var6 = this.dstSamples * var5; var5 >= 0; var6 -= this.dstSamples) {
         this.srcColorModel.getComponents(var4[var5], this.row, var6);
         var5--;
      }

      if (this.sampleDiff != 0) {
         System.arraycopy(this.row, this.sampleDiff, this.row, 0, this.dstSamples * var3);
      }

      this.dst.setPixels(var1, var2, var3, this.row);
   }

    void setPixel(int var1, int var2, int[] var3) {
      this.setPixels(var1, var2, 1, var3);
   }

    void getPixel(int var1, int var2, int[] var3) {
      throw new UnsupportedOperationException("implement me");
   }

    WritableRaster getRaster() {
      return this.dst.getRaster();
   }

    int getSourceWidth() {
      return this.dst.getSourceWidth();
   }

    void done() {
      this.dst.done();
   }
}
} // namespace png
} // namespace sixlegs
} // namespace com
