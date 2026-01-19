#include "zombie/asset/Asset.h"

namespace zombie {
namespace asset {

protected Asset::Asset(AssetPath var1, AssetManager var2) {
    // TODO: Implement Asset
    return nullptr;
}

State Asset::getState() {
    // TODO: Implement getState
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

void Asset::onCreated(State var1) {
    // TODO: Implement onCreated
}

int Asset::getRefCount() {
    // TODO: Implement getRefCount
    return 0;
}

ObserverCallback Asset::getObserverCb() {
    // TODO: Implement getObserverCb
    return nullptr;
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

void Asset::addDependency(Asset var1) {
    // TODO: Implement addDependency
}

void Asset::removeDependency(Asset var1) {
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

void Asset::setAssetParams(AssetParams var1) {
    // TODO: Implement setAssetParams
}

} // namespace asset
} // namespace zombie
