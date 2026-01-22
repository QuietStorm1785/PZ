#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/DebugFileWatcher.h"
#include "zombie/PredicatedFileWatcher.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetManager/AssetParams.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/asset/AssetTask_RunFileTask.h"
#include "zombie/core/skinnedmodel/model/ModelMesh/MeshAssetParams.h"
#include "zombie/core/skinnedmodel/model/jassimp/ProcessedAiScene.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class MeshAssetManager : public AssetManager {
public:
    static const MeshAssetManager instance = std::make_shared<MeshAssetManager>();
   private const std::unordered_set<std::string> m_watchedFiles = std::make_unique<std::unordered_set<>>();
    const PredicatedFileWatcher m_watcher = std::make_shared<PredicatedFileWatcher>(MeshAssetManager::isWatched, MeshAssetManager::watchedFileChanged);

    private MeshAssetManager() {
      DebugFileWatcher.instance.push_back(this.m_watcher);
   }

    void startLoading(Asset var1) {
    ModelMesh var2 = (ModelMesh)var1;
    FileSystem var3 = this.getOwner().getFileSystem();
    FileTask_LoadMesh var4 = std::make_shared<FileTask_LoadMesh>(var2, var3, var2x -> this.loadCallback(var2, var2x));
      var4.setPriority(6);
    AssetTask_RunFileTask var5 = std::make_shared<AssetTask_RunFileTask>(var4, var1);
      this.setTask(var1, var5);
      var5.execute();
   }

    void loadCallback(ModelMesh var1, void* var2) {
      if (dynamic_cast<ProcessedAiScene*>(var2) != nullptr) {
         var1.onLoadedX((ProcessedAiScene)var2);
         this.onLoadingSucceeded(var1);
      } else if (dynamic_cast<ModelTxt*>(var2) != nullptr) {
         var1.onLoadedTxt((ModelTxt)var2);
         this.onLoadingSucceeded(var1);
      } else {
         DebugLog.General.warn("Failed to load asset: " + var1.getPath());
         this.onLoadingFailed(var1);
      }
   }

    Asset createAsset(AssetPath var1, AssetParams var2) {
      return std::make_shared<ModelMesh>(var1, this, (MeshAssetParams)var2);
   }

    void destroyAsset(Asset var1) {
   }

    static bool isWatched(const std::string& var0) {
      if (!StringUtils.endsWithIgnoreCase(var0, ".fbx") && !StringUtils.endsWithIgnoreCase(var0, ".x")) {
    return false;
      } else {
    std::string var1 = ZomboidFileSystem.instance.getString(var0);
         return instance.m_watchedFiles.contains(var1);
      }
   }

    static void watchedFileChanged(const std::string& var0) {
      DebugLog.Asset.printf("%s changed\n", new Object[]{var0});
    std::string var1 = ZomboidFileSystem.instance.getString(var0);
      instance.getAssetTable().forEachValue(var1x -> {
    ModelMesh var2 = (ModelMesh)var1x;
         if (!var2.empty() && var1.equalsIgnoreCase(var2.m_fullPath)) {
    MeshAssetParams var3 = std::make_shared<MeshAssetParams>();
            var3.animationsMesh = var2.m_animationsMesh;
            var3.bStatic = var2.bStatic;
            instance.reload(var1x, var3);
         }

    return true;
      });
   }

    void addWatchedFile(const std::string& var1) {
      this.m_watchedFiles.push_back(var1);
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
