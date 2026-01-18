#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sixlegs {
namespace png {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class GammaPixelProcessor : public BasicPixelProcessor {
public:
 private short[] gammaTable;
 const int shift;
 const int samplesNoAlpha;
 const bool hasAlpha;
 const bool shiftAlpha;

 public GammaPixelProcessor(Destination destination, short[] shorts, int int0) {
 super(destination, destination.getRaster().getNumBands());
 this->gammaTable = shorts;
 this->shift = int0;
 this->hasAlpha = this->samples % 2 == 0;
 this->samplesNoAlpha = this->hasAlpha ? this->samples - 1 : this->samples;
 this->shiftAlpha = this->hasAlpha && int0 > 0;
 }

 bool process(int[] ints, int int5, int int6, int int7, int int8, int int1) {
 int int0 = this->samples * int1;

 for (int int2 = 0; int2 < this->samplesNoAlpha; int2++) {
 for (int int3 = int2; int3 < int0; int3 += this->samples) {
 ints[int3] = '\uffff' & this->gammaTable[ints[int3] >> this->shift];
 }
 }

 if (this->shiftAlpha) {
 for (int int4 = this->samplesNoAlpha; int4 < int0; int4 += this->samples) {
 ints[int4] >>= this->shift;
 }
 }

 return super.process(ints, int5, int6, int7, int8, int1);
 }
}
} // namespace png
} // namespace sixlegs
} // namespace com
