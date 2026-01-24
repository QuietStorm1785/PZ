
#pragma once
#include <memory>
#include <functional>
#include "zombie/asset/Asset/ObserverCallback.h"
#include "zombie/asset/Asset/State.h"

namespace zombie {
namespace asset {

namespace zombie {
namespace asset {

class Asset;
class AssetTask;

class Asset$PRIVATE {
public:
   Asset& asset;
   State m_current_state = State::EMPTY;
   State m_desired_state = State::EMPTY;
   int m_empty_dep_count = 1;
   int m_failed_dep_count = 0;
   std::function<void(State, State, Asset&)> m_cb;
   std::shared_ptr<AssetTask> m_task;

   explicit Asset$PRIVATE(Asset& asset_)
      : asset(asset_) {}


    void onCreated(State state) {
        assert(m_empty_dep_count == 1);
        assert(m_failed_dep_count == 0);
        m_current_state = state;
        m_desired_state = State::READY;
        m_failed_dep_count = (state == State::FAILURE) ? 1 : 0;
        m_empty_dep_count = 0;
    }

    void addDependency(Asset& dep);

    void removeDependency(Asset& dep);

    void onStateChanged(State oldState, State newState, Asset& dep);


    void onLoadingSucceeded();


    void onLoadingFailed();

    void checkState();

private:
    // Helper for assertions (replace with assert or custom logic as needed)
    inline void assert(bool condition) const {
        if (!condition) throw std::logic_error("Asset$PRIVATE assertion failed");
    }
};

} // namespace asset
} // namespace zombie
