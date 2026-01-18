#include "zombie/asset/Asset.h"

namespace zombie {
namespace asset {

protected
Asset::Asset(AssetPath assetPath, AssetManager assetManager) {
 // TODO: Implement Asset
 return nullptr;
}

bool Asset::isEmpty() {
 // TODO: Implement isEmpty
 return false;
}

bool Asset::isReady() {
 // TODO: Implement isReady
 return false;
}

bool Asset::isFailure() {
 // TODO: Implement isFailure
 return false;
}

void Asset::onCreated(Asset.State state) {
 // TODO: Implement onCreated
}

int Asset::getRefCount() {
 // TODO: Implement getRefCount
 return 0;
}

AssetPath Asset::getPath() {
 // TODO: Implement getPath
 return {};
}

AssetManager Asset::getAssetManager() {
 // TODO: Implement getAssetManager
 return {};
}

void Asset::onBeforeReady() {
 // TODO: Implement onBeforeReady
}

void Asset::onBeforeEmpty() {
 // TODO: Implement onBeforeEmpty
}

void Asset::addDependency(Asset dependent_asset) {
 // TODO: Implement addDependency
}

void Asset::removeDependency(Asset dependent_asset) {
 // TODO: Implement removeDependency
}

int Asset::addRef() {
 // TODO: Implement addRef
 return 0;
}

int Asset::rmRef() {
 // TODO: Implement rmRef
 return 0;
}

void Asset::setAssetParams(AssetManager.AssetParams params) {
 // TODO: Implement setAssetParams
}

void Asset::invoke(Asset.State oldState, Asset.State newState, Asset asset) {
 // TODO: Implement invoke
}

void Asset::onCreated(Asset.State state) {
 // TODO: Implement onCreated
}

void Asset::addDependency(Asset asset) {
 // TODO: Implement addDependency
}

void Asset::removeDependency(Asset asset) {
 // TODO: Implement removeDependency
}

void Asset::onStateChanged(Asset.State arg0, Asset.State arg1, Asset arg2) {
 // TODO: Implement onStateChanged
}

void Asset::onLoadingSucceeded() {
 // TODO: Implement onLoadingSucceeded
}

void Asset::onLoadingFailed() {
 // TODO: Implement onLoadingFailed
}

void Asset::checkState() {
 // TODO: Implement checkState
}

} // namespace asset
} // namespace zombie
