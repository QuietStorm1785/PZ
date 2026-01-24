
#include "zombie/asset/Asset.h"

namespace zombie::asset {

Asset::Asset(AssetPath path, AssetManager asset_manager)
    : m_asset_manager(asset_manager), m_path(path), m_ref_count(0), m_priv(std::make_shared<PRIVATE>(this)) {}

State Asset::getState() const {
    return m_priv->m_current_state;
}

bool Asset::isEmpty() const {
    return m_priv->m_current_state == State::EMPTY;
}

bool Asset::isReady() const {
    return m_priv->m_current_state == State::READY;
}

bool Asset::isFailure() const {
    return m_priv->m_current_state == State::FAILURE;
}

void Asset::onCreated(State state) {
    m_priv->onCreated(state);
}

int Asset::getRefCount() const {
    return m_ref_count;
}

std::shared_ptr<ObserverCallback> Asset::getObserverCb() {
    if (!m_priv->m_cb) {
        m_priv->m_cb = std::make_shared<ObserverCallback>();
    }
    return m_priv->m_cb;
}

AssetPath Asset::getPath() const {
    return m_path;
}

AssetManager Asset::getAssetManager() const {
    return m_asset_manager;
}

void Asset::onBeforeReady() {
    // No-op by default
}

void Asset::onBeforeEmpty() {
    // No-op by default
}

void Asset::addDependency(Asset& asset) {
    m_priv->addDependency(asset);
}

void Asset::removeDependency(Asset& asset) {
    m_priv->removeDependency(asset);
}

int Asset::addRef() {
    return ++m_ref_count;
}

int Asset::rmRef() {
    return --m_ref_count;
}

void Asset::setAssetParams(const AssetParams& params) {
    // No-op by default
}

} // namespace asset

std::shared_ptr<ObserverCallback> Asset::getObserverCb() {
    if (!m_priv->m_cb) {
        m_priv->m_cb = std::make_shared<ObserverCallback>();
    }
    return m_priv->m_cb;
}

AssetPath Asset::getPath() {
    return m_path;
}

AssetManager Asset::getAssetManager() {
    return m_asset_manager;
}

void Asset::onBeforeReady() {
    // No-op by default
}

void Asset::onBeforeEmpty() {
    // No-op by default
}

void Asset::addDependency(Asset& var1) {
    m_priv->addDependency(var1);
}

void Asset::removeDependency(Asset& var1) {
    m_priv->removeDependency(var1);
}

int Asset::addRef() {
    return ++m_ref_count;
}

int Asset::rmRef() {
    return --m_ref_count;
}

void Asset::setAssetParams(const AssetParams& var1) {
    // No-op by default
}

} // namespace asset
} // namespace zombie
