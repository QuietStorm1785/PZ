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

class AssetTask {
public:
 Asset m_asset;

public
 AssetTask(Asset asset) { this->m_asset = asset; }

public
 void execute();

public
 void cancel();
}
} // namespace asset
} // namespace zombie
