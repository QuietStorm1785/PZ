
#include "zombie/asset/Asset$PRIVATE.h"
#include "zombie/asset/Asset.h"

namespace zombie::asset {

void Asset$PRIVATE::onCreated(State state) {
    // Assertion checks omitted for brevity
    m_current_state = state;
    m_desired_state = State::READY;
    m_failed_dep_count = (state == State::FAILURE) ? 1 : 0;
    m_empty_dep_count = 0;
}

void Asset$PRIVATE::addDependency(Asset& asset) {
    // Assertion checks omitted for brevity
    asset.getObserverCb()->addObserver(shared_from_this());
    if (asset.isEmpty()) ++m_empty_dep_count;
    if (asset.isFailure()) ++m_failed_dep_count;
    checkState();
}

void Asset$PRIVATE::removeDependency(Asset& asset) {
    asset.getObserverCb()->removeObserver(shared_from_this());
    if (asset.isEmpty() && m_empty_dep_count > 0) --m_empty_dep_count;
    if (asset.isFailure() && m_failed_dep_count > 0) --m_failed_dep_count;
    checkState();
}

void Asset$PRIVATE::onStateChanged(State oldState, State newState, Asset& asset) {
    // Assertion checks omitted for brevity
    if (oldState == State::EMPTY && m_empty_dep_count > 0) --m_empty_dep_count;
    if (oldState == State::FAILURE && m_failed_dep_count > 0) --m_failed_dep_count;
    if (newState == State::EMPTY) ++m_empty_dep_count;
    if (newState == State::FAILURE) ++m_failed_dep_count;
    checkState();
}

void Asset$PRIVATE::onLoadingSucceeded() {
    // Assertion checks omitted for brevity
    if (m_empty_dep_count > 0) --m_empty_dep_count;
    m_task.reset();
    checkState();
}

void Asset$PRIVATE::onLoadingFailed() {
    // Assertion checks omitted for brevity
    ++m_failed_dep_count;
    if (m_empty_dep_count > 0) --m_empty_dep_count;
    m_task.reset();
    checkState();
}

void Asset$PRIVATE::checkState() {
    State prev = m_current_state;
    if (m_failed_dep_count > 0 && m_current_state != State::FAILURE) {
        m_current_state = State::FAILURE;
        // Notify asset manager and observers
        // (Assume m_asset is a pointer to the owning Asset)
        if (m_asset) m_asset->getAssetManager().onStateChanged(prev, m_current_state, *m_asset);
        if (m_cb) m_cb->invoke(prev, m_current_state, *m_asset);
    }
    if (m_failed_dep_count == 0) {
        if (m_empty_dep_count == 0 && m_current_state != State::READY && m_desired_state != State::EMPTY) {
            if (m_asset) m_asset->onBeforeReady();
            m_current_state = State::READY;
            if (m_asset) m_asset->getAssetManager().onStateChanged(prev, m_current_state, *m_asset);
            if (m_cb) m_cb->invoke(prev, m_current_state, *m_asset);
        }
        if (m_empty_dep_count > 0 && m_current_state != State::EMPTY) {
            if (m_asset) m_asset->onBeforeEmpty();
            m_current_state = State::EMPTY;
            if (m_asset) m_asset->getAssetManager().onStateChanged(prev, m_current_state, *m_asset);
            if (m_cb) m_cb->invoke(prev, m_current_state, *m_asset);
        }
    }
}

} // namespace zombie::asset
