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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class BuildingScore {
public:
 float weapons;
 float food;
 float wood;
 float defense;
 IsoBuilding building;
 int size;
 int safety;

 public BuildingScore(IsoBuilding buildingx) {
 this->building = buildingx;
 }
}
} // namespace areas
} // namespace iso
} // namespace zombie
