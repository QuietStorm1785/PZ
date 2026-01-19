#pragma once
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace asset {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AssetType {
public:
 static const AssetType INVALID_ASSET_TYPE = new AssetType("");
 long type;

public
 AssetType(std::string_view typeName) {
 CRC32 crc32 = new CRC32();
 crc32.update(typeName.getBytes());
 this->type = crc32.getValue();
 }
}
} // namespace asset
} // namespace zombie
