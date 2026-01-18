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

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class AnimNodeAssetManager : public AssetManager {
public:
 static const AnimNodeAssetManager instance = new AnimNodeAssetManager();

 void startLoading(Asset asset) {
 AnimNodeAsset animNodeAsset = (AnimNodeAsset)asset;
 animNodeAsset.m_animNode = AnimNode.Parse(asset.getPath().getPath());
 if (animNodeAsset.m_animNode == nullptr) {
 this->onLoadingFailed(asset);
 } else {
 this->onLoadingSucceeded(asset);
 }
 }

 void onStateChanged(Asset.State state0, Asset.State state1, Asset asset) {
 super.onStateChanged(state0, state1, asset);
 if (state1 == Asset.State.READY) {
 }
 }

 Asset createAsset(AssetPath assetPath, AssetManager.AssetParams var2) {
 return new AnimNodeAsset(assetPath, this);
 }

 void destroyAsset(Asset var1) {
 }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
