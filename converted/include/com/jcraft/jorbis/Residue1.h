#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace jcraft {
namespace jorbis {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class Residue1 : public Residue0 {
public:
 int inverse(Block block, void* object, float[][] floats, int[] ints, int int2) {
 int int0 = 0;

 for (int int1 = 0; int1 < int2; int1++) {
 if (ints[int1] != 0) {
 floats[int0++] = floats[int1];
 }
 }

 return int0 != 0 ? _01inverse(block, object, floats, int0, 1) : 0;
 }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
