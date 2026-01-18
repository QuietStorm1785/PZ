#pragma once
#include "javax/xml/bind/annotation/XmlIDREF.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Anim2DBlendTriangle {
public:
 Anim2DBlend node1;
 Anim2DBlend node2;
 Anim2DBlend node3;

 static double sign(float float5, float float0, float float2, float float4,
 float float3, float float1) {
 return (float5 - float3) * (float4 - float1) -
 (float2 - float3) * (float0 - float1);
 }

 static bool PointInTriangle(float float0, float float1, float float2,
 float float3, float float4, float float5,
 float float6, float float7) {
 bool boolean0 = sign(float0, float1, float2, float3, float4, float5) < 0.0;
 bool boolean1 = sign(float0, float1, float4, float5, float6, float7) < 0.0;
 bool boolean2 = sign(float0, float1, float6, float7, float2, float3) < 0.0;
 return boolean0 = = boolean1 && boolean1 == boolean2;
 }

 bool Contains(float float0, float float1) { return PointInTriangle(); }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
