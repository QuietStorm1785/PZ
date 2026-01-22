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


class VertexPositionNormalTangentTexture {
public:
    Vector3 Position;
    Vector3 Normal;
    Vector3 Tangent;
    Vector2 TextureCoordinates;

    public VertexPositionNormalTangentTexture(Vector3 var1, Vector3 var2, Vector3 var3, Vector2 var4) {
      this.Position = var1;
      this.Normal = var2;
      this.Tangent = var3;
      this.TextureCoordinates = var4;
   }

    public VertexPositionNormalTangentTexture() {
      this.Position = std::make_shared<Vector3>(0.0F, 0.0F, 0.0F);
      this.Normal = std::make_shared<Vector3>(0.0F, 0.0F, 1.0F);
      this.Tangent = std::make_shared<Vector3>(0.0F, 1.0F, 0.0F);
      this.TextureCoordinates = std::make_shared<Vector2>(0.0F, 0.0F);
   }

    void put(ByteBuffer var1) {
      var1.putFloat(this.Position.x());
      var1.putFloat(this.Position.y());
      var1.putFloat(this.Position.z());
      var1.putFloat(this.Normal.x());
      var1.putFloat(this.Normal.y());
      var1.putFloat(this.Normal.z());
      var1.putFloat(this.Tangent.x());
      var1.putFloat(this.Tangent.y());
      var1.putFloat(this.Tangent.z());
      var1.putFloat(this.TextureCoordinates.x);
      var1.putFloat(this.TextureCoordinates.y);
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
