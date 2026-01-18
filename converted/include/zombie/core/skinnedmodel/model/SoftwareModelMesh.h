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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class SoftwareModelMesh {
public:
 public int[] indicesUnskinned;
 public VertexPositionNormalTangentTextureSkin[] verticesUnskinned;
 std::string Texture;
 VertexBufferObject vb;

 public SoftwareModelMesh(VertexPositionNormalTangentTextureSkin[] vertexPositionNormalTangentTextureSkins, int[] ints) {
 this->indicesUnskinned = ints;
 this->verticesUnskinned = vertexPositionNormalTangentTextureSkins;
 }

 public SoftwareModelMesh(VertexPositionNormalTangentTexture[] vertexPositionNormalTangentTextures, int[] ints) {
 this->indicesUnskinned = ints;
 this->verticesUnskinned = new VertexPositionNormalTangentTextureSkin[vertexPositionNormalTangentTextures.length];

 for (int int0 = 0; int0 < vertexPositionNormalTangentTextures.length; int0++) {
 VertexPositionNormalTangentTexture vertexPositionNormalTangentTexture = vertexPositionNormalTangentTextures[int0];
 this->verticesUnskinned[int0] = std::make_unique<VertexPositionNormalTangentTextureSkin>();
 this->verticesUnskinned[int0].Position = new Vector3(
 vertexPositionNormalTangentTexture.Position.x(),
 vertexPositionNormalTangentTexture.Position.y(),
 vertexPositionNormalTangentTexture.Position.z()
 );
 this->verticesUnskinned[int0].Normal = new Vector3(
 vertexPositionNormalTangentTexture.Normal.x(), vertexPositionNormalTangentTexture.Normal.y(), vertexPositionNormalTangentTexture.Normal.z()
 );
 this->verticesUnskinned[int0].TextureCoordinates = new Vector2(
 vertexPositionNormalTangentTexture.TextureCoordinates.x, vertexPositionNormalTangentTexture.TextureCoordinates.y
 );
 }
 }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
