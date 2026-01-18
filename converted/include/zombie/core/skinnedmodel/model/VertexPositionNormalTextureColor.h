#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Color.h"
#include "zombie/core/skinnedmodel/Vector3.h"
#include "zombie/iso/Vector2.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class VertexPositionNormalTextureColor {
public:
 Color Color;
 Vector3 Position;
 Vector3 Normal;
 Vector2 TextureCoordinates;

 void put(ByteBuffer byteBuffer) {
 byteBuffer.putFloat(this->Position.x());
 byteBuffer.putFloat(this->Position.y());
 byteBuffer.putFloat(this->Position.z());
 byteBuffer.putFloat(this->Normal.x());
 byteBuffer.putFloat(this->Normal.y());
 byteBuffer.putFloat(this->Normal.z());
 byteBuffer.putFloat(this->TextureCoordinates.x);
 byteBuffer.putFloat(this->TextureCoordinates.y);
 byteBuffer.put((byte)(this->Color.r * 255.0F);
 byteBuffer.put((byte)(this->Color.g * 255.0F);
 byteBuffer.put((byte)(this->Color.b * 255.0F);
 }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
