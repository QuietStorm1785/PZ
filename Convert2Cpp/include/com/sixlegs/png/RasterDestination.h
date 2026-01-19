#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/awt/image/WritableRaster.h"

namespace com {
namespace sixlegs {
namespace png {


class RasterDestination : public Destination {
public:
    const WritableRaster raster;
    const int sourceWidth;

    public RasterDestination(WritableRaster var1, int var2) {
      this.raster = var1;
      this.sourceWidth = var2;
   }

    void setPixels(int var1, int var2, int var3, int[] var4) {
      this.raster.setPixels(var1, var2, var3, 1, var4);
   }

    void setPixel(int var1, int var2, int[] var3) {
      this.raster.setPixel(var1, var2, var3);
   }

    void getPixel(int var1, int var2, int[] var3) {
      this.raster.getPixel(var1, var2, var3);
   }

    WritableRaster getRaster() {
      return this.raster;
   }

    int getSourceWidth() {
      return this.sourceWidth;
   }

    void done() {
   }
}
} // namespace png
} // namespace sixlegs
} // namespace com
