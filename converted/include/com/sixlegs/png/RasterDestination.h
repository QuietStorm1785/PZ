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

class RasterDestination : public Destination {
public:
  const WritableRaster raster;
  const int sourceWidth;

public
  RasterDestination(WritableRaster writableRaster, int int0) {
    this.raster = writableRaster;
    this.sourceWidth = int0;
  }

  void setPixels(int int0, int int1, int int2, int[] ints) {
    this.raster.setPixels(int0, int1, int2, 1, ints);
  }

  void setPixel(int int0, int int1, int[] ints) {
    this.raster.setPixel(int0, int1, ints);
  }

  void getPixel(int int0, int int1, int[] ints) {
    this.raster.getPixel(int0, int1, ints);
  }

  WritableRaster getRaster() { return this.raster; }

  int getSourceWidth() { return this.sourceWidth; }

  void done() {}
}
} // namespace png
} // namespace sixlegs
} // namespace com
