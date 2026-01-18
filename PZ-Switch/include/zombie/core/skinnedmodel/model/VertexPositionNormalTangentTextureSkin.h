#pragma once
#include "zombie/core/skinnedmodel/Vector3.h"
#include "zombie/core/skinnedmodel/Vector4.h"
#include "zombie/iso/Vector2.h"
#include <cstdint>
#include <filesystem>
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

/**
 * Created by LEMMYATI on 03/01/14.
 */
class VertexPositionNormalTangentTextureSkin {
public:
 Vector3 Position;
 Vector3 Normal;
 Vector3 Tangent;
 Vector2 TextureCoordinates;
 Vector4 BlendWeights;
 UInt4 BlendIndices;

public
 VertexPositionNormalTangentTextureSkin() {}

public
 VertexPositionNormalTangentTextureSkin(Vector3 position, Vector3 normal,
 Vector3 tangent, Vector2 uv,
 Vector4 blendweights,
 UInt4 blendIndices) {
 this->Position = position;
 this->Normal = normal;
 this->Tangent = tangent;
 this->TextureCoordinates = uv;
 this->BlendWeights = blendweights;
 this->BlendIndices = blendIndices;
 }

 void put(ByteBuffer buf) {
 buf.putFloat(this->Position.x());
 buf.putFloat(this->Position.y());
 buf.putFloat(this->Position.z());
 buf.putFloat(this->Normal.x());
 buf.putFloat(this->Normal.y());
 buf.putFloat(this->Normal.z());
 buf.putFloat(this->Tangent.x());
 buf.putFloat(this->Tangent.y());
 buf.putFloat(this->Tangent.z());
 buf.putFloat(this->TextureCoordinates.x);
 buf.putFloat(this->TextureCoordinates.y);
 buf.putFloat(this->BlendWeights.x);
 buf.putFloat(this->BlendWeights.y);
 buf.putFloat(this->BlendWeights.z);
 buf.putFloat(this->BlendWeights.w);
 buf.putFloat(this->BlendIndices.X);
 buf.putFloat(this->BlendIndices.Y);
 buf.putFloat(this->BlendIndices.Z);
 buf.putFloat(this->BlendIndices.W);
 }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
