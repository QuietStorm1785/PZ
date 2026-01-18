#pragma once
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/asset/AssetType.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/animation/AnimationClip.h"
#include "zombie/core/skinnedmodel/model/jassimp/ProcessedAiScene.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AnimationAsset : public Asset {
public:
public
 HashMap<String, AnimationClip> AnimationClips;
public
 AnimationAsset.AnimationAssetParams assetParams;
 SkinningData skinningData;
 std::string modelManagerKey;
public
 ModelManager.ModAnimations modAnimations;
 static const AssetType ASSET_TYPE = new AssetType("Animation");

public
 AnimationAsset(AssetPath path, AssetManager manager,
 AnimationAsset.AnimationAssetParams params) {
 super(path, manager);
 this->assetParams = params;
 }

 void onLoadedX(ProcessedAiScene processedAiScene) {
 processedAiScene.applyToAnimation(this);
 }

 void onLoadedTxt(ModelTxt modelTxt) {
 ModelLoader.instance.applyToAnimation(modelTxt, this);
 }

 void onBeforeReady() {
 super.onBeforeReady();
 if (this->assetParams != nullptr) {
 this->assetParams.animationsMesh = nullptr;
 this->assetParams = nullptr;
 }
 }

 void setAssetParams(AssetManager.AssetParams params) {
 this->assetParams = (AnimationAsset.AnimationAssetParams)params;
 }

 AssetType getType() { return ASSET_TYPE; }

public
 static class AnimationAssetParams extends AssetManager.AssetParams {
 ModelMesh animationsMesh;
 }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
