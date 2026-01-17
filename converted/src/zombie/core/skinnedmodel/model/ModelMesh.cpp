#include "zombie/core/skinnedmodel/model/ModelMesh.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {

public
ModelMesh::ModelMesh(AssetPath path, AssetManager manager,
                     ModelMesh.MeshAssetParams params) {
  // TODO: Implement ModelMesh
  return nullptr;
}

void ModelMesh::onLoadedX(ProcessedAiScene processedAiScene) {
  // TODO: Implement onLoadedX
}

void ModelMesh::onLoadedTxt(ModelTxt modelTxt) {
  // TODO: Implement onLoadedTxt
}

void ModelMesh::SetVertexBuffer(VertexBufferObject _vb) {
  // TODO: Implement SetVertexBuffer
}

void ModelMesh::Draw(Shader shader) {
  // TODO: Implement Draw
}

void ModelMesh::onBeforeReady() {
  // TODO: Implement onBeforeReady
}

bool ModelMesh::isReady() {
  // TODO: Implement isReady
  return false;
}

void ModelMesh::setAssetParams(AssetManager.AssetParams params) {
  // TODO: Implement setAssetParams
}

AssetType ModelMesh::getType() {
  // TODO: Implement getType
  return {};
}

void ModelMesh::clear() {
  // TODO: Implement clear
}

} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
