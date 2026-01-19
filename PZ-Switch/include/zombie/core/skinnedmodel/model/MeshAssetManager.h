#pragma once
#include "zombie/DebugFileWatcher.h"
#include "zombie/PredicatedFileWatcher.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/asset/AssetTask_RunFileTask.h"
#include "zombie/core/skinnedmodel/model/jassimp/ProcessedAiScene.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/util/StringUtils.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class MeshAssetManager : public AssetManager {
public:
 static const MeshAssetManager instance = new MeshAssetManager();
private
 HashSet<String> m_watchedFiles = std::make_unique<HashSet<>>();
 const PredicatedFileWatcher m_watcher = new PredicatedFileWatcher(
 MeshAssetManager::isWatched, MeshAssetManager::watchedFileChanged);

private
 MeshAssetManager() { DebugFileWatcher.instance.add(this->m_watcher); }

 void startLoading(Asset asset) {
 ModelMesh modelMesh = (ModelMesh)asset;
 FileSystem fileSystem = this->getOwner().getFileSystem();
 FileTask_LoadMesh fileTask_LoadMesh = new FileTask_LoadMesh(
 modelMesh, fileSystem, object->this->loadCallback(modelMesh, object);
 fileTask_LoadMesh.setPriority(6);
 AssetTask_RunFileTask assetTask_RunFileTask =
 new AssetTask_RunFileTask(fileTask_LoadMesh, asset);
 this->setTask(asset, assetTask_RunFileTask);
 assetTask_RunFileTask.execute();
 }

 void loadCallback(ModelMesh modelMesh, void *object) {
 if (object instanceof ProcessedAiScene) {
 modelMesh.onLoadedX((ProcessedAiScene)object);
 this->onLoadingSucceeded(modelMesh);
 } else if (object instanceof ModelTxt) {
 modelMesh.onLoadedTxt((ModelTxt)object);
 this->onLoadingSucceeded(modelMesh);
 } else {
 DebugLog.General.warn("Failed to load asset: " + modelMesh.getPath());
 this->onLoadingFailed(modelMesh);
 }
 }

 Asset createAsset(AssetPath assetPath, AssetManager.AssetParams assetParams) {
 return new ModelMesh(assetPath, this,
 (ModelMesh.MeshAssetParams)assetParams);
 }

 void destroyAsset(Asset var1) {}

 static bool isWatched(std::string_view string0) {
 if (!StringUtils.endsWithIgnoreCase(string0, ".fbx") &&
 !StringUtils.endsWithIgnoreCase(string0, ".x")) {
 return false;
 } else {
 std::string string1 = ZomboidFileSystem.instance.getString(string0);
 return instance.m_watchedFiles.contains(string1);
 }
 }

 static void watchedFileChanged(std::string_view string0) {
 DebugLog.Asset.printf("%s changed\n", string0);
 std::string string1 = ZomboidFileSystem.instance.getString(string0);
 instance.getAssetTable().forEachValue(asset->{
 ModelMesh modelMesh = (ModelMesh)asset;
 if (!modelMesh.empty() &&
 string1.equalsIgnoreCase(modelMesh.m_fullPath) {
 ModelMesh.MeshAssetParams meshAssetParams =
 new ModelMesh.MeshAssetParams();
 meshAssetParams.animationsMesh = modelMesh.m_animationsMesh;
 meshAssetParams.bStatic = modelMesh.bStatic;
 instance.reload(asset, meshAssetParams);
 }

 return true;
 });
 }

 void addWatchedFile(std::string_view string) {
 this->m_watchedFiles.add(string);
 }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
