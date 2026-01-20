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


class VertexPositionNormalTextureColor {
public:
    Color Color;
    Vector3 Position;
    Vector3 Normal;
    Vector2 TextureCoordinates;

    void put(ByteBuffer var1) {
      var1.putFloat(this.Position.x());
      var1.putFloat(this.Position.y());
      var1.putFloat(this.Position.z());
      var1.putFloat(this.Normal.x());
      var1.putFloat(this.Normal.y());
      var1.putFloat(this.Normal.z());
      var1.putFloat(this.TextureCoordinates.x);
      var1.putFloat(this.TextureCoordinates.y);
      var1.put((byte)(this.Color.r * 255.0F));
      var1.put((byte)(this.Color.g * 255.0F));
      var1.put((byte)(this.Color.b * 255.0F));
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
