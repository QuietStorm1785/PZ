#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace asset {


class AssetType {
public:
    static const AssetType INVALID_ASSET_TYPE = new AssetType("");
    long type;

    public AssetType(const std::string& var1) {
    CRC32 var2 = new CRC32();
      var2.update(var1.getBytes());
      this.type = var2.getValue();
   }
}
} // namespace asset
} // namespace zombie
