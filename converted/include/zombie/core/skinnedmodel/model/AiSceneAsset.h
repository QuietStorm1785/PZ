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
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class AiSceneAsset : public Asset {
public:
 AiScene m_scene;
 EnumSet<AiPostProcessSteps> m_post_process_step_set;
 AiSceneAsset.AiSceneAssetParams assetParams;
 static const AssetType ASSET_TYPE = new AssetType("AiScene");

 protected AiSceneAsset(AssetPath assetPath, AssetManager assetManager, AiSceneAsset.AiSceneAssetParams aiSceneAssetParams) {
 super(assetPath, assetManager);
 this->assetParams = aiSceneAssetParams;
 this->m_scene = nullptr;
 this->m_post_process_step_set = aiSceneAssetParams.post_process_step_set;
 }

 AssetType getType() {
 return ASSET_TYPE;
 }

 public static class AiSceneAssetParams extends AssetManager.AssetParams {
 EnumSet<AiPostProcessSteps> post_process_step_set;
 }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
