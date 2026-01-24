
#include "zombie/asset/Asset$ObserverCallback.h"
#include "zombie/asset/AssetStateObserver.h"

namespace zombie::asset {

void Asset$ObserverCallback::invoke(State oldState, State newState, Asset& asset) {
    for (const auto& observer : m_observers) {
        if (observer) {
            observer->onStateChanged(oldState, newState, asset);
        }
    }
}

} // namespace zombie::asset
