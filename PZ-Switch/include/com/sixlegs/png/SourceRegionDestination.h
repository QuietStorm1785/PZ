#pragma once
#include "java/awt/Rectangle.h"
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

class SourceRegionDestination : public Destination {
public:
 const Destination dst;
 const int xoff;
 const int yoff;
 const int xlen;
 const int ylen;
 const int samples;

public
 SourceRegionDestination(Destination destination, Rectangle rectangle) {
 this->dst = destination;
 this->xoff = rectangle.x;
 this->yoff = rectangle.y;
 this->xlen = rectangle.width;
 this->ylen = rectangle.height;
 this->samples = destination.getRaster().getNumBands();
 }

 void setPixels(int int2, int int0, int int4, int[] ints) {
 if (int0 >= this->yoff && int0 < this->yoff + this->ylen) {
 int int1 = Math.max(int2, this->xoff);
 int int3 = Math.min(int2 + int4, this->xoff + this->xlen) - int1;
 if (int3 > 0) {
 if (int1 > int2) {
 System.arraycopy(ints, int1 * this->samples, ints, 0,
 int3 * this->samples);
 }

 this->dst.setPixels(int1 - this->xoff, int0 - this->yoff, int3, ints);
 }
 }
 }

 void setPixel(int int0, int int1, int[] ints) {
 int0 -= this->xoff;
 int1 -= this->yoff;
 if (int0 >= 0 && int1 >= 0 && int0 < this->xlen && int1 < this->ylen) {
 this->dst.setPixel(int0, int1, ints);
 }
 }

 void getPixel(int var1, int var2, int[] var3) {
 throw std::make_unique<UnsupportedOperationException>();
 }

 WritableRaster getRaster() { return this->dst.getRaster(); }

 int getSourceWidth() { return this->dst.getSourceWidth(); }

 void done() { this->dst.done(); }
}
} // namespace png
} // namespace sixlegs
} // namespace com
