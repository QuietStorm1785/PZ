#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/asset/AssetType.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class AnimNodeAsset : public Asset {
public:
 static const AssetType ASSET_TYPE = new AssetType("AnimNode");
 AnimNode m_animNode;

 protected AnimNodeAsset(AssetPath assetPath, AssetManager assetManager) {
 super(assetPath, assetManager);
 }

 AssetType getType() {
 return ASSET_TYPE;
 }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
