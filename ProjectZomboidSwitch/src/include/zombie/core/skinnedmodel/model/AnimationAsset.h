#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetManager/AssetParams.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/asset/AssetType.h"
#include "zombie/core/skinnedmodel/ModelManager/ModAnimations.h"
#include "zombie/core/skinnedmodel/animation/AnimationClip.h"
#include "zombie/core/skinnedmodel/model/AnimationAsset/AnimationAssetParams.h"
#include "zombie/core/skinnedmodel/model/jassimp/ProcessedAiScene.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class AnimationAsset : public Asset {
public:
   public std::unordered_map<std::string, AnimationClip> AnimationClips;
    AnimationAssetParams assetParams;
    SkinningData skinningData;
    std::string modelManagerKey;
    ModAnimations modAnimations;
    static const AssetType ASSET_TYPE = std::make_shared<AssetType>("Animation");

    public AnimationAsset(AssetPath var1, AssetManager var2, AnimationAssetParams var3) {
      super(var1, var2);
      this.assetParams = var3;
   }

    void onLoadedX(ProcessedAiScene var1) {
      var1.applyToAnimation(this);
   }

    void onLoadedTxt(ModelTxt var1) {
      ModelLoader.instance.applyToAnimation(var1, this);
   }

    void onBeforeReady() {
      super.onBeforeReady();
      if (this.assetParams != nullptr) {
         this.assetParams.animationsMesh = nullptr;
         this.assetParams = nullptr;
      }
   }

    void setAssetParams(AssetParams var1) {
      this.assetParams = (AnimationAssetParams)var1;
   }

    AssetType getType() {
    return ASSET_TYPE;
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
