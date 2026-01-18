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
#include "zombie/asset/AssetPath.h"
#include "zombie/asset/AssetTask_RunFileTask.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/fileSystem/FileTask.h"
#include <filesystem>

namespace zombie {
namespace worldMap {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class WorldMapDataAssetManager : public AssetManager {
public:
 static const WorldMapDataAssetManager instance = new WorldMapDataAssetManager();

 void startLoading(Asset asset) {
 WorldMapData worldMapData = (WorldMapData)asset;
 FileSystem fileSystem = this->getOwner().getFileSystem();
 std::string string = asset.getPath().getPath();
 void* object;
 if (Files.exists(Paths.get(string + ".bin"))) {
 object = new FileTask_LoadWorldMapBinary(worldMapData, string + ".bin", fileSystem, objectx -> this->loadCallback(worldMapData, objectx);
 } else {
 object = new FileTask_LoadWorldMapXML(worldMapData, string, fileSystem, objectx -> this->loadCallback(worldMapData, objectx);
 }

 ((FileTask)object).setPriority(4);
 AssetTask_RunFileTask assetTask_RunFileTask = new AssetTask_RunFileTask((FileTask)object, asset);
 this->setTask(asset, assetTask_RunFileTask);
 assetTask_RunFileTask.execute();
 }

 void loadCallback(WorldMapData worldMapData, void* object) {
 if (object == Boolean.TRUE) {
 worldMapData.onLoaded();
 this->onLoadingSucceeded(worldMapData);
 } else {
 DebugLog.General.warn("Failed to load asset: " + worldMapData.getPath());
 this->onLoadingFailed(worldMapData);
 }
 }

 Asset createAsset(AssetPath assetPath, AssetManager.AssetParams assetParams) {
 WorldMapData worldMapData = new WorldMapData(assetPath, this, assetParams);
 DebugFileWatcher.instance.add(new PredicatedFileWatcher(assetPath.getPath(), var3x -> this->reload(worldMapData, assetParams));
 return worldMapData;
 }

 void destroyAsset(Asset var1) {
 }
}
} // namespace worldMap
} // namespace zombie
