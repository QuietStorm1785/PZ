
#pragma once
#include <vector>
#include <memory>
#include "zombie/asset/Asset/State.h"

namespace zombie::asset {

class Asset;
class AssetStateObserver;

class Asset$ObserverCallback {
public:
   using ObserverPtr = std::shared_ptr<AssetStateObserver>;
   std::vector<ObserverPtr> m_observers;

   void addObserver(const ObserverPtr& observer) {
      m_observers.push_back(observer);
   }

   void removeObserver(const ObserverPtr& observer) {
      m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
   }

   void invoke(State oldState, State newState, Asset& asset);
};

} // namespace zombie::asset
