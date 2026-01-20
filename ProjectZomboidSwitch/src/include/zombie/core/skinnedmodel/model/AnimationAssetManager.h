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
#include "zombie/asset/AssetTask_RunFileTask.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/model/AnimationAsset/AnimationAssetParams.h"
#include "zombie/core/skinnedmodel/model/jassimp/ProcessedAiScene.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/fileSystem/FileSystem.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class AnimationAssetManager : public AssetManager {
public:
    static const AnimationAssetManager instance = std::make_shared<AnimationAssetManager>();

    void startLoading(Asset var1) {
    AnimationAsset var2 = (AnimationAsset)var1;
    FileSystem var3 = this.getOwner().getFileSystem();
    FileTask_LoadAnimation var4 = std::make_shared<FileTask_LoadAnimation>(var2, var3, var2x -> this.loadCallback(var2, var2x));
      var4.setPriority(4);
    std::string var5 = var1.getPath().getPath().toLowerCase();
      if (var5.endsWith("bob_idle") || var5.endsWith("bob_walk") || var5.endsWith("bob_run")) {
         var4.setPriority(6);
      }

    AssetTask_RunFileTask var6 = std::make_shared<AssetTask_RunFileTask>(var4, var1);
      this.setTask(var1, var6);
      var6.execute();
   }

    void loadCallback(AnimationAsset var1, void* var2) {
      if (dynamic_cast<ProcessedAiScene*>(var2) != nullptr) {
         var1.onLoadedX((ProcessedAiScene)var2);
         this.onLoadingSucceeded(var1);
         ModelManager.instance.animationAssetLoaded(var1);
      } else if (dynamic_cast<ModelTxt*>(var2) != nullptr) {
         var1.onLoadedTxt((ModelTxt)var2);
         this.onLoadingSucceeded(var1);
         ModelManager.instance.animationAssetLoaded(var1);
      } else {
         DebugLog.General.warn("Failed to load asset: " + var1.getPath());
         this.onLoadingFailed(var1);
      }
   }

    Asset createAsset(AssetPath var1, AssetParams var2) {
      return std::make_shared<AnimationAsset>(var1, this, (AnimationAssetParams)var2);
   }

    void destroyAsset(Asset var1) {
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
