#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace jobs {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class JobSquareUpdate : public RegionJob {
public:
 int worldSquareX;
 int worldSquareY;
 int worldSquareZ;
 uint8_t newSquareFlags;

 protected JobSquareUpdate() {
 super(RegionJobType.SquareUpdate);
 }

 int getWorldSquareX() {
 return this->worldSquareX;
 }

 int getWorldSquareY() {
 return this->worldSquareY;
 }

 int getWorldSquareZ() {
 return this->worldSquareZ;
 }

 uint8_t getNewSquareFlags() {
 return this->newSquareFlags;
 }
}
} // namespace jobs
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
