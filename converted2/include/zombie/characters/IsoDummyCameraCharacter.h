#pragma once
#include "zombie/iso/IsoCamera.h"
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

class IsoDummyCameraCharacter : public IsoGameCharacter {
public:
public
  IsoDummyCameraCharacter(float x, float y, float z) {
    super(nullptr, x, y, z);
    IsoCamera.CamCharacter = this;
  }

  void update() {}
}
} // namespace characters
} // namespace zombie
