#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "jassimp/AiPostProcessSteps.h"
#include "jassimp/AiScene.h"
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/asset/AssetType.h"
#include "zombie/core/skinnedmodel/model/AiSceneAsset/AiSceneAssetParams.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class AiSceneAsset : public Asset {
public:
    AiScene m_scene;
   EnumSet<AiPostProcessSteps> m_post_process_step_set;
    AiSceneAssetParams assetParams;
    static const AssetType ASSET_TYPE = std::make_shared<AssetType>("AiScene");

    protected AiSceneAsset(AssetPath var1, AssetManager var2, AiSceneAssetParams var3) {
      super(var1, var2);
      this.assetParams = var3;
      this.m_scene = nullptr;
      this.m_post_process_step_set = var3.post_process_step_set;
   }

    AssetType getType() {
    return ASSET_TYPE;
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
