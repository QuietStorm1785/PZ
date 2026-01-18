#include "zombie/asset/AssetManager.h"

namespace zombie {
namespace asset {

void AssetManager::create(AssetType type, AssetManagers owner) {
 // TODO: Implement create
}

void AssetManager::destroy() {
 // TODO: Implement destroy
}

void AssetManager::removeUnreferenced() {
 // TODO: Implement removeUnreferenced
}

Asset AssetManager::load(AssetPath path) {
 // TODO: Implement load
 return {};
}

Asset AssetManager::load(AssetPath path, AssetManager.AssetParams params) {
 // TODO: Implement load
 return {};
}

void AssetManager::load(Asset asset) {
 // TODO: Implement load
}

void AssetManager::unload(AssetPath path) {
 // TODO: Implement unload
}

void AssetManager::unload(Asset asset) {
 // TODO: Implement unload
}

void AssetManager::reload(AssetPath path) {
 // TODO: Implement reload
}

void AssetManager::reload(Asset asset) {
 // TODO: Implement reload
}

void AssetManager::reload(Asset asset, AssetManager.AssetParams params) {
 // TODO: Implement reload
}

void AssetManager::enableUnload(bool enable) {
 // TODO: Implement enableUnload
}

void AssetManager::doLoad(Asset asset, AssetManager.AssetParams assetParams) {
 // TODO: Implement doLoad
}

void AssetManager::doUnload(Asset asset) {
 // TODO: Implement doUnload
}

void AssetManager::onStateChanged(Asset.State old_state, Asset.State new_state, Asset asset) {
 // TODO: Implement onStateChanged
}

void AssetManager::startLoading(Asset asset) {
 // TODO: Implement startLoading
}

void AssetManager::onLoadingSucceeded(Asset asset) {
 // TODO: Implement onLoadingSucceeded
}

void AssetManager::onLoadingFailed(Asset asset) {
 // TODO: Implement onLoadingFailed
}

void AssetManager::setTask(Asset asset, AssetTask assetTask) {
 // TODO: Implement setTask
}

bool AssetManager::loadDataFromFile(Asset var1, IFile var2) {
 // TODO: Implement loadDataFromFile
 return false;
}

void AssetManager::unloadData(Asset var1) {
 // TODO: Implement unloadData
}

AssetManagers AssetManager::getOwner() {
 // TODO: Implement getOwner
 return {};
}

Asset AssetManager::get(AssetPath assetPath) {
 // TODO: Implement get
 return {};
}

} // namespace asset
} // namespace zombie
