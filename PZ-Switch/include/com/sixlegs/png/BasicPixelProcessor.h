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

class BasicPixelProcessor : public PixelProcessor {
public:
 const Destination dst;
 const int samples;

public
 BasicPixelProcessor(Destination destination, int int0) {
 this->dst = destination;
 this->samples = int0;
 }

 bool process(int[] ints, int int1, int int0, int var4, int int2, int int3) {
 if (int0 == 1) {
 this->dst.setPixels(int1, int2, int3, ints);
 } else {
 int int4 = int1;
 int int5 = 0;

 for (int int6 = this->samples * int3; int5 < int6; int5 += this->samples) {
 for (int int7 = 0; int7 < this->samples; int7++) {
 ints[int7] = ints[int5 + int7];
 }

 this->dst.setPixel(int4, int2, ints);
 int4 += int0;
 }
 }

 return true;
 }
}
} // namespace png
} // namespace sixlegs
} // namespace com
