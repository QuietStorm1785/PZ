#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace radio {
namespace StorySounds {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Turbo
 */
class DataPoint {
public:
  float time = 0.0F;
  float intensity = 0.0F;

public
  DataPoint(float _time, float _intensity) {
    this.setTime(_time);
    this.setIntensity(_intensity);
  }

  float getTime() { return this.time; }

  void setTime(float _time) {
    if (_time < 0.0F) {
      _time = 0.0F;
    }

    if (_time > 1.0F) {
      _time = 1.0F;
    }

    this.time = _time;
  }

  float getIntensity() { return this.intensity; }

  void setIntensity(float _intensity) {
    if (_intensity < 0.0F) {
      _intensity = 0.0F;
    }

    if (_intensity > 1.0F) {
      _intensity = 1.0F;
    }

    this.intensity = _intensity;
  }
}
} // namespace StorySounds
} // namespace radio
} // namespace zombie
