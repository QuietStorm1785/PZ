#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace stash {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class StashBuilding {
public:
 int buildingX;
 int buildingY;
 std::string stashName;

public
 StashBuilding(const std::string &_stashName, int _buildingX, int _buildingY) {
 this->stashName = _stashName;
 this->buildingX = _buildingX;
 this->buildingY = _buildingY;
 }

 std::string getName() { return this->stashName; }
}
} // namespace stash
} // namespace core
} // namespace zombie
