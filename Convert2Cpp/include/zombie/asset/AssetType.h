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
    static auto INVALID_ASSET_TYPE = std::make_shared<AssetType>("");
    long type;

    public AssetType(const std::string& var1) {
    auto var2 = std::make_shared<CRC32>();
      var2.update(var1.getBytes());
      this.type = var2.getValue();
   }
}
} // namespace asset
} // namespace zombie
