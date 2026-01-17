#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace asset {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AssetStateObserver {
public:
  virtual ~AssetStateObserver() = default;
  void onStateChanged(Asset.State oldState, Asset.State newState, Asset asset);
}
} // namespace asset
} // namespace zombie
