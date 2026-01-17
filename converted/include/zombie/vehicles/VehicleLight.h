#pragma once
#include "org/joml/Vector3f.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace vehicles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class VehicleLight {
public:
  bool active;
  const Vector3f offset = new Vector3f();
  float dist = 16.0F;
  float intensity = 1.0F;
  float dot = 0.96F;
  int focusing = 0;

  bool getActive() { return this.active; }

  void setActive(bool _active) { this.active = _active; }

  int getFocusing() { return this.focusing; }

  float getIntensity() { return this.intensity; }

  float getDistanization() { return this.dist; }

  bool canFocusingUp() { return this.focusing != 0; }

  bool canFocusingDown() { return this.focusing != 1; }

  void setFocusingUp() {
    if (this.focusing != 0) {
      if (this.focusing < 4) {
        this.focusing = 4;
      } else if (this.focusing < 10) {
        this.focusing = 10;
      } else if (this.focusing < 30) {
        this.focusing = 30;
      } else if (this.focusing < 100) {
        this.focusing = 100;
      } else {
        this.focusing = 0;
      }
    }
  }

  void setFocusingDown() {
    if (this.focusing != 1) {
      if (this.focusing == 0) {
        this.focusing = 100;
      } else if (this.focusing > 30) {
        this.focusing = 30;
      } else if (this.focusing > 10) {
        this.focusing = 10;
      } else if (this.focusing > 4) {
        this.focusing = 4;
      } else {
        this.focusing = 1;
      }
    }
  }

  void save(ByteBuffer output) {
    output.put((byte)(this.active ? 1 : 0));
    output.putFloat(this.offset.x);
    output.putFloat(this.offset.y);
    output.putFloat(this.intensity);
    output.putFloat(this.dist);
    output.putInt(this.focusing);
  }

  void load(ByteBuffer input, int WorldVersion) {
    this.active = input.get() == 1;
    if (WorldVersion >= 135) {
      this.offset.x = input.getFloat();
      this.offset.y = input.getFloat();
      this.intensity = input.getFloat();
      this.dist = input.getFloat();
      this.focusing = input.getInt();
    }
  }
}
} // namespace vehicles
} // namespace zombie
