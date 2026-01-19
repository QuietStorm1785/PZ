#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace asset {


class AssetType {
:
    static const AssetType INVALID_ASSET_TYPE = new AssetType("");
    long type;

     AssetType(std::string_view var1) {
    CRC32 var2 = new CRC32();
      var2.update(var1.getBytes());
      this.type = var2.getValue();
   }
}
} // namespace asset
} // namespace zombie
