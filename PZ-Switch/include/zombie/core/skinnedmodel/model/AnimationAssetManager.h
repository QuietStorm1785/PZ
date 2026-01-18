#pragma once
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/asset/AssetTask_RunFileTask.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/model/jassimp/ProcessedAiScene.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/fileSystem/FileSystem.h"
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

class AnimationAssetManager : public AssetManager {
public:
 static const AnimationAssetManager instance = new AnimationAssetManager();

 void startLoading(Asset asset) {
 AnimationAsset animationAsset = (AnimationAsset)asset;
 FileSystem fileSystem = this->getOwner().getFileSystem();
 FileTask_LoadAnimation fileTask_LoadAnimation = new FileTask_LoadAnimation(
 animationAsset, fileSystem,
 object->this->loadCallback(animationAsset, object);
 fileTask_LoadAnimation.setPriority(4);
 std::string string = asset.getPath().getPath().toLowerCase();
 if (string.endsWith("bob_idle") || string.endsWith("bob_walk") ||
 string.endsWith("bob_run")) {
 fileTask_LoadAnimation.setPriority(6);
 }

 AssetTask_RunFileTask assetTask_RunFileTask =
 new AssetTask_RunFileTask(fileTask_LoadAnimation, asset);
 this->setTask(asset, assetTask_RunFileTask);
 assetTask_RunFileTask.execute();
 }

 void loadCallback(AnimationAsset animationAsset, void *object) {
 if (object instanceof ProcessedAiScene) {
 animationAsset.onLoadedX((ProcessedAiScene)object);
 this->onLoadingSucceeded(animationAsset);
 ModelManager.instance.animationAssetLoaded(animationAsset);
 } else if (object instanceof ModelTxt) {
 animationAsset.onLoadedTxt((ModelTxt)object);
 this->onLoadingSucceeded(animationAsset);
 ModelManager.instance.animationAssetLoaded(animationAsset);
 } else {
 DebugLog.General.warn("Failed to load asset: " +
 animationAsset.getPath());
 this->onLoadingFailed(animationAsset);
 }
 }

 Asset createAsset(AssetPath assetPath, AssetManager.AssetParams assetParams) {
 return new AnimationAsset(assetPath, this,
 (AnimationAsset.AnimationAssetParams)assetParams);
 }

 void destroyAsset(Asset var1) {}
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
