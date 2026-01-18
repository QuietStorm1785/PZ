#pragma once
#include "org/joml/Vector4f.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace math {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Vector4 : public Vector4f {
public:
public
 Vector4() {}

public
 Vector4(float float0, float float1, float float2, float float3) {
 super(float0, float1, float2, float3);
 }

public
 Vector4(org.lwjgl.util.vector.Vector4f vector4f) {
 super(vector4f.x, vector4f.y, vector4f.z, vector4f.w);
 }

public
 org.lwjgl.util.vector.Vector4f Get() {
 org.lwjgl.util.vector.Vector4f vector4f =
 new org.lwjgl.util.vector.Vector4f();
 vector4f.set(this->x, this->y, this->z, this->w);
 return vector4f;
 }

 void Set(org.lwjgl.util.vector.Vector4f vector4f) {
 this->x = vector4f.x;
 this->y = vector4f.y;
 this->z = vector4f.z;
 this->w = vector4f.w;
 }
}
} // namespace math
} // namespace core
} // namespace zombie
