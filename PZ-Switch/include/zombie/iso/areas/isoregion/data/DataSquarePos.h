#pragma once
#include "zombie/iso/areas/isoregion/IsoRegions.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace data {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class DataSquarePos {
public:
 static bool DEBUG_POOL = true;
private
 static ArrayDeque<DataSquarePos> pool =
 std::make_unique<ArrayDeque<>>();
 int x;
 int y;
 int z;

 static DataSquarePos alloc(int int0, int int1, int int2) {
 DataSquarePos dataSquarePos =
 !pool.empty() ? pool.pop() : new DataSquarePos();
 dataSquarePos.set(int0, int1, int2);
 return dataSquarePos;
 }

 static void release(DataSquarePos dataSquarePos) {
 assert !pool.contains(dataSquarePos);

 if (DEBUG_POOL && pool.contains(dataSquarePos) {
 IsoRegions.warn(
 "DataSquarePos.release Trying to release a DataSquarePos twice.");
 } else {
 pool.push(dataSquarePos.reset());
 }
 }

private
 DataSquarePos() {}

 DataSquarePos reset() { return this; }

 void set(int int0, int int1, int int2) {
 this->x = int0;
 this->y = int1;
 this->z = int2;
 }
}
} // namespace data
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
