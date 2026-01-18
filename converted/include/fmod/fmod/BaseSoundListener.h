#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace fmod {
namespace fmod {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class BaseSoundListener {
public:
  int index;
  float x;
  float y;
  float z;

public
  BaseSoundListener(int arg0) { this.index = arg0; }

  void setPos(float arg0, float arg1, float arg2) {
    this.x = arg0;
    this.y = arg1;
    this.z = arg2;
  }

public
  abstract void tick();
}
} // namespace fmod
} // namespace fmod
