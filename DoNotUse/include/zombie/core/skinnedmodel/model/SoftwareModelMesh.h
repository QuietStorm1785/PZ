#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/Vector3.h"
#include "zombie/iso/Vector2.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class SoftwareModelMesh {
public:
   public int[] indicesUnskinned;
   public VertexPositionNormalTangentTextureSkin[] verticesUnskinned;
    std::string Texture;
    VertexBufferObject vb;

    public SoftwareModelMesh(VertexPositionNormalTangentTextureSkin[] var1, int[] var2) {
      this.indicesUnskinned = var2;
      this.verticesUnskinned = var1;
   }

    public SoftwareModelMesh(VertexPositionNormalTangentTexture[] var1, int[] var2) {
      this.indicesUnskinned = var2;
      this.verticesUnskinned = new VertexPositionNormalTangentTextureSkin[var1.length];

      for (int var3 = 0; var3 < var1.length; var3++) {
    VertexPositionNormalTangentTexture var4 = var1[var3];
         this.verticesUnskinned[var3] = std::make_unique<VertexPositionNormalTangentTextureSkin>();
         this.verticesUnskinned[var3].Position = std::make_shared<Vector3>(var4.Position.x(), var4.Position.y(), var4.Position.z());
         this.verticesUnskinned[var3].Normal = std::make_shared<Vector3>(var4.Normal.x(), var4.Normal.y(), var4.Normal.z());
         this.verticesUnskinned[var3].TextureCoordinates = std::make_shared<Vector2>(var4.TextureCoordinates.x, var4.TextureCoordinates.y);
      }
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
