#include <string>
#include "zombie\core\skinnedmodel\model/MeshAssetManager.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {

private MeshAssetManager::MeshAssetManager() {
    // TODO: Implement MeshAssetManager
    return nullptr;
}

void MeshAssetManager::startLoading(Asset var1) {
    // TODO: Implement startLoading
}

void MeshAssetManager::loadCallback(ModelMesh var1, void* var2) {
    // TODO: Implement loadCallback
}

Asset MeshAssetManager::createAsset(AssetPath var1, AssetParams var2) {
    // TODO: Implement createAsset
    return {};
}

void MeshAssetManager::destroyAsset(Asset var1) {
    // TODO: Implement destroyAsset
}

bool MeshAssetManager::isWatched(const std::string& var0) {
    // TODO: Implement isWatched
    return false;
}

void MeshAssetManager::watchedFileChanged(const std::string& var0) {
    // TODO: Implement watchedFileChanged
}

void MeshAssetManager::addWatchedFile(const std::string& var1) {
    // TODO: Implement addWatchedFile
}

} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
