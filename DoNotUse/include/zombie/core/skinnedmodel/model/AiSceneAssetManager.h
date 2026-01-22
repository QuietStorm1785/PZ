#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "jassimp/AiScene.h"
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetManager/AssetParams.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/asset/AssetTask_RunFileTask.h"
#include "zombie/core/skinnedmodel/model/AiSceneAsset/AiSceneAssetParams.h"
#include "zombie/core/skinnedmodel/model/AiSceneAssetManager/FileTask_LoadAiScene.h"
#include "zombie/fileSystem/FileSystem.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class AiSceneAssetManager : public AssetManager {
public:
    static const AiSceneAssetManager instance = std::make_shared<AiSceneAssetManager>();

    void startLoading(Asset var1) {
    FileSystem var2 = var1.getAssetManager().getOwner().getFileSystem();
      FileTask_LoadAiScene var3 = std::make_shared<FileTask_LoadAiScene>(
         var1.getPath().getPath(), ((AiSceneAsset)var1).m_post_process_step_set, var2x -> this.onFileTaskFinished((AiSceneAsset)var1, var2x), var2
      );
    AssetTask_RunFileTask var4 = std::make_shared<AssetTask_RunFileTask>(var3, var1);
      this.setTask(var1, var4);
      var4.execute();
   }

    void onFileTaskFinished(AiSceneAsset var1, void* var2) {
      if (dynamic_cast<AiScene*>(var2) != nullptr) {
         var1.m_scene = (AiScene)var2;
         this.onLoadingSucceeded(var1);
      } else {
         this.onLoadingFailed(var1);
      }
   }

    Asset createAsset(AssetPath var1, AssetParams var2) {
      return std::make_shared<AiSceneAsset>(var1, this, (AiSceneAssetParams)var2);
   }

    void destroyAsset(Asset var1) {
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
