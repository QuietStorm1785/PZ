#pragma once
#include "java/awt/image/ComponentColorModel.h"
#include "java/awt/image/IndexColorModel.h"
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

class ConvertIndexedDestination : public Destination {
public:
 const Destination dst;
 const IndexColorModel srcColorModel;
 const int srcSamples;
 const int dstSamples;
 const int sampleDiff;
private
 int[] row;

public
 ConvertIndexedDestination(Destination destination, int int0,
 IndexColorModel indexColorModel,
 ComponentColorModel componentColorModel) {
 this->dst = destination;
 this->srcColorModel = indexColorModel;
 this->srcSamples = indexColorModel.getNumComponents();
 this->dstSamples = componentColorModel.getNumComponents();
 this->sampleDiff = this->srcSamples - this->dstSamples;
 this->row = new int[int0 * this->dstSamples + this->sampleDiff];
 }

 void setPixels(int int3, int int4, int int1, int[] ints) {
 int int0 = int1 - 1;

 for (int int2 = this->dstSamples * int0; int0 >= 0;
 int2 -= this->dstSamples) {
 this->srcColorModel.getComponents(ints[int0], this->row, int2);
 int0--;
 }

 if (this->sampleDiff != 0) {
 System.arraycopy(this->row, this->sampleDiff, this->row, 0,
 this->dstSamples * int1);
 }

 this->dst.setPixels(int3, int4, int1, this->row);
 }

 void setPixel(int int0, int int1, int[] ints) {
 this->setPixels(int0, int1, 1, ints);
 }

 void getPixel(int var1, int var2, int[] var3) {
 throw UnsupportedOperationException("implement me");
 }

 WritableRaster getRaster() { return this->dst.getRaster(); }

 int getSourceWidth() { return this->dst.getSourceWidth(); }

 void done() { this->dst.done(); }
}
} // namespace png
} // namespace sixlegs
} // namespace com
