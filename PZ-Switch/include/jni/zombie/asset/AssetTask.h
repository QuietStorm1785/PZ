#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace asset {

class AssetTask {
:
    Asset m_asset;

     AssetTask(Asset var1) {
      this.m_asset = var1;
   }

    abstract void execute();

    abstract void cancel();
}
} // namespace asset
} // namespace zombie
