#include "zombie/core/skinnedmodel/model/MeshAssetManager.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {

private
MeshAssetManager::MeshAssetManager() {
 // TODO: Implement MeshAssetManager
 return nullptr;
}

void MeshAssetManager::startLoading(Asset asset) {
 // TODO: Implement startLoading
}

void MeshAssetManager::loadCallback(ModelMesh modelMesh, void *object) {
 // TODO: Implement loadCallback
}

Asset MeshAssetManager::createAsset(AssetPath assetPath,
 AssetManager.AssetParams assetParams) {
 // TODO: Implement createAsset
 return {};
}

void MeshAssetManager::destroyAsset(Asset var1) {
 // TODO: Implement destroyAsset
}

bool MeshAssetManager::isWatched(const std::string &string0) {
 // TODO: Implement isWatched
 return false;
}

void MeshAssetManager::watchedFileChanged(const std::string &string0) {
 // TODO: Implement watchedFileChanged
}

void MeshAssetManager::addWatchedFile(const std::string &string) {
 // TODO: Implement addWatchedFile
}

} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
