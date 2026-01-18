#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace com {
namespace jcraft {
namespace jorbis {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Residue2 : public Residue0 {
public:
 int inverse(Block block, void *object, float[][] floats, int[] ints,
 int int1) {
 int int0 = 0;
 int0 = 0;

 while (int0 < int1 && ints[int0] == 0) {
 int0++;
 }

 return int0 = = int1 ? 0 : _2inverse(block, object, floats, int1);
 }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
