#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IsoLuaCharacter : public IsoGameCharacter {
public:
public
 IsoLuaCharacter(float float0, float float1, float float2) {
 super(nullptr, float0, float1, float2);
 this->descriptor = SurvivorFactory.CreateSurvivor();
 this->descriptor.setInstance(this);
 SurvivorDesc survivorDesc = this->descriptor;
 this->InitSpriteParts(survivorDesc);
 }

 void update() {}
}
} // namespace characters
} // namespace zombie
