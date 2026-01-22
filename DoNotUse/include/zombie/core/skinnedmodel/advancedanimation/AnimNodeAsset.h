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


class AnimNodeAsset : public Asset {
public:
    static const AssetType ASSET_TYPE = std::make_shared<AssetType>("AnimNode");
    AnimNode m_animNode;

    protected AnimNodeAsset(AssetPath var1, AssetManager var2) {
      super(var1, var2);
   }

    AssetType getType() {
    return ASSET_TYPE;
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
