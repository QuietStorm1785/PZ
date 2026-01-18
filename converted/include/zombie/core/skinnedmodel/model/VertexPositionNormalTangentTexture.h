#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/Vector3.h"
#include "zombie/iso/Vector2.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Created by LEMMYATI on 09/03/14.
 */
class VertexPositionNormalTangentTexture {
public:
 Vector3 Position;
 Vector3 Normal;
 Vector3 Tangent;
 Vector2 TextureCoordinates;

 public VertexPositionNormalTangentTexture(Vector3 position, Vector3 normal, Vector3 tangent, Vector2 uv) {
 this->Position = position;
 this->Normal = normal;
 this->Tangent = tangent;
 this->TextureCoordinates = uv;
 }

 public VertexPositionNormalTangentTexture() {
 this->Position = new Vector3(0.0F, 0.0F, 0.0F);
 this->Normal = new Vector3(0.0F, 0.0F, 1.0F);
 this->Tangent = new Vector3(0.0F, 1.0F, 0.0F);
 this->TextureCoordinates = new Vector2(0.0F, 0.0F);
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
 }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
