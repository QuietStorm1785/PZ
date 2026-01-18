#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Created by LEMMYATI on 03/01/14.
 */
class Vector4 {
public:
  float x;
  float y;
  float z;
  float w;

public
  Vector4() { this(0.0F, 0.0F, 0.0F, 0.0F); }

public
  Vector4(float _x, float _y, float _z, float _w) {
    this.x = _x;
    this.y = _y;
    this.z = _z;
    this.w = _w;
  }

public
  Vector4(Vector4 vec) { this.set(vec); }

  Vector4 set(float _x, float _y, float _z, float _w) {
    this.x = _x;
    this.y = _y;
    this.z = _z;
    this.w = _w;
    return this;
  }

  Vector4 set(Vector4 vec) { return this.set(vec.x, vec.y, vec.z, vec.w); }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
