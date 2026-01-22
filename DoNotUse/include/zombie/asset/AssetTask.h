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
public:
    Asset m_asset;

    public AssetTask(Asset var1) {
      this.m_asset = var1;
   }

   public abstract void execute();

   public abstract void cancel();
}
} // namespace asset
} // namespace zombie
