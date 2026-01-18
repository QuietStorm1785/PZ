#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace vehicles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class EngineRPMData {
public:
 float gearChange;
 float afterGearChange;

public
 EngineRPMData() {}

public
 EngineRPMData(float _gearChange, float _afterGearChange) {
 this->gearChange = _gearChange;
 this->afterGearChange = _afterGearChange;
 }

 void reset() {
 this->gearChange = 0.0F;
 this->afterGearChange = 0.0F;
 }
}
} // namespace vehicles
} // namespace zombie
