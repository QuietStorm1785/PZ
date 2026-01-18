#pragma once
#include "zombie/core/Color.h"
#include "zombie/core/skinnedmodel/HelperFunctions.h"
#include "zombie/core/skinnedmodel/Vector3.h"
#include "zombie/iso/Vector2.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class VertexDefinitions {
public:
 class VertexPositionColour {
 Vector3 Position;
 int Colour;

 public
 VertexPositionColour(Vector3 vector3, Color color) {
 this->Position = vector3;
 this->Colour = HelperFunctions.ToRgba(color);
 }

 public
 VertexPositionColour(float float0, float float1, float float2,
 Color color) {
 this->Position = new Vector3(float0, float1, float2);
 this->Colour = HelperFunctions.ToRgba(color);
 }
 }

 class VertexPositionNormal {
 Vector3 Position;
 Vector3 Normal;

 public
 VertexPositionNormal(Vector3 vector30, Vector3 vector31, Vector2 var4) {
 this->Position = vector30;
 this->Normal = vector31;
 }

 public
 VertexPositionNormal(float float0, float float1, float float2, float float3,
 float float4, float float5) {
 this->Position = new Vector3(float0, float1, float2);
 this->Normal = new Vector3(float3, float4, float5);
 }
 }

 class VertexPositionNormalTangentTexture {
 Vector3 Position;
 Vector3 Normal;
 Vector3 Tangent;
 Vector2 TextureCoordinates;

 public
 VertexPositionNormalTangentTexture(Vector3 vector30, Vector3 vector31,
 Vector3 vector32, Vector2 vector) {
 this->Position = vector30;
 this->Normal = vector31;
 this->Tangent = vector32;
 this->TextureCoordinates = vector;
 }

 public
 VertexPositionNormalTangentTexture(float float0, float float1, float float2,
 float float3, float float4, float float5,
 float float6, float float7, float float8,
 float float9, float float10) {
 this->Position = new Vector3(float0, float1, float2);
 this->Normal = new Vector3(float3, float4, float5);
 this->Tangent = new Vector3(float6, float7, float8);
 this->TextureCoordinates = new Vector2(float9, float10);
 }
 }

 class VertexPositionNormalTexture {
 Vector3 Position;
 Vector3 Normal;
 Vector2 TextureCoordinates;

 public
 VertexPositionNormalTexture(Vector3 vector30, Vector3 vector31,
 Vector2 vector) {
 this->Position = vector30;
 this->Normal = vector31;
 this->TextureCoordinates = vector;
 }

 public
 VertexPositionNormalTexture(float float0, float float1, float float2,
 float float3, float float4, float float5,
 float float6, float float7) {
 this->Position = new Vector3(float0, float1, float2);
 this->Normal = new Vector3(float3, float4, float5);
 this->TextureCoordinates = new Vector2(float6, float7);
 }
 }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
