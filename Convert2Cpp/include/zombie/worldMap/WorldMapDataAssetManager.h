#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/DebugFileWatcher.h"
#include "zombie/PredicatedFileWatcher.h"
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetManager/AssetParams.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/asset/AssetTask_RunFileTask.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/fileSystem/FileTask.h"
#include <filesystem>

namespace zombie {
namespace worldMap {


class WorldMapDataAssetManager : public AssetManager {
public:
    static auto instance = std::make_shared<WorldMapDataAssetManager>();

    void startLoading(Asset var1) {
    WorldMapData var2 = static_cast<WorldMapData>(var1);
    FileSystem var3 = this.getOwner().getFileSystem();
    std::string var5 = var1.getPath().getPath();
    void* var4;
      if (Files.exists(Paths.get(var5 + ".bin"))) {
         var4 = new FileTask_LoadWorldMapBinary(var2, var5 + ".bin", var3, var2x -> this.loadCallback(var2, var2x));
      } else {
         var4 = new FileTask_LoadWorldMapXML(var2, var5, var3, var2x -> this.loadCallback(var2, var2x));
      }

      var4.setPriority(4);
    auto var6 = std::make_shared<AssetTask_RunFileTask>(static_cast<FileTask>(var4), var1);
      this.setTask(var1, var6);
      var6.execute();
   }

    void loadCallback(WorldMapData var1, void* var2) {
      if (var2 == Boolean.TRUE) {
         var1.onLoaded();
         this.onLoadingSucceeded(var1);
      } else {
         DebugLog.General.warn("Failed to load asset: " + var1.getPath());
         this.onLoadingFailed(var1);
      }
   }

    Asset createAsset(AssetPath var1, AssetParams var2) {
    auto var3 = std::make_shared<WorldMapData>(var1, this, var2);
      DebugFileWatcher.instance.add(new PredicatedFileWatcher(var1.getPath(), var3x -> this.reload(var3, var2)));
    return var3;
   }

    void destroyAsset(Asset var1) {
   }
}
} // namespace worldMap
} // namespace zombie
