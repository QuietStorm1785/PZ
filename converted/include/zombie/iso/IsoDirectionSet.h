#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class IsoDirectionSet {
public:
 int set = 0;

 static IsoDirections rotate(IsoDirections dir, int amount) {
 amount += dir.index();
 amount %= 8;
 return IsoDirections.fromIndex(amount);
 }

 IsoDirections getNext() {
 for (int int0 = 0; int0 < 8; int0++) {
 int int1 = 1 << int0;
 if ((this->set & int1) != 0) {
 this->set ^= int1;
 return IsoDirections.fromIndex(int0);
 }
 }

 return IsoDirections.Max;
 }
}
} // namespace iso
} // namespace zombie
