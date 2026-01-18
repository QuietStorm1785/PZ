#pragma once
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

class TransGammaPixelProcessor : public BasicPixelProcessor {
public:
private
 short[] gammaTable;
private
 int[] trans;
 const int shift;
 const int max;
 const int samplesNoAlpha;
private
 int[] temp;

public
 TransGammaPixelProcessor(Destination destination, short[] shorts, int[] ints,
 int int0) {
 super(destination, destination.getRaster().getNumBands());
 this->gammaTable = shorts;
 this->trans = ints;
 this->shift = int0;
 this->max = shorts.length - 1;
 this->samplesNoAlpha = this->samples - 1;
 this->temp = new int[this->samples * destination.getSourceWidth()];
 }

 bool process(int[] ints, int int6, int int7, int int8, int int9, int int1) {
 int int0 = int1 * this->samplesNoAlpha;
 int int2 = 0;

 for (int int3 = 0; int2 < int0; int3 += this->samples) {
 bool boolean0 = false;

 for (int int4 = 0; int4 < this->samplesNoAlpha; int4++) {
 int int5 = ints[int2 + int4];
 boolean0 = boolean0 || int5 != this->trans[int4];
 this->temp[int3 + int4] = '\uffff' & this->gammaTable[int5 >> this->shift];
 }

 this->temp[int3 + this->samplesNoAlpha] = boolean0 ? this->max : 0;
 int2 += this->samplesNoAlpha;
 }

 return super.process(this->temp, int6, int7, int8, int9, int1);
 }
}
} // namespace png
} // namespace sixlegs
} // namespace com
