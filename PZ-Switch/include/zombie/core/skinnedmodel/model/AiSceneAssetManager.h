#pragma once
#include "jassimp/AiPostProcessSteps.h"
#include "jassimp/AiScene.h"
#include "jassimp/Jassimp.h"
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/asset/AssetTask_RunFileTask.h"
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/fileSystem/FileTask.h"
#include "zombie/fileSystem/IFileTaskCallback.h"
#include <algorithm>
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

class AiSceneAssetManager : public AssetManager {
public:
 static const AiSceneAssetManager instance = new AiSceneAssetManager();

 void startLoading(Asset asset) {
 FileSystem fileSystem = asset.getAssetManager().getOwner().getFileSystem();
 AiSceneAssetManager.FileTask_LoadAiScene fileTask_LoadAiScene =
 new AiSceneAssetManager.FileTask_LoadAiScene(
 asset.getPath().getPath(),
 ((AiSceneAsset)asset).m_post_process_step_set,
 object->this->onFileTaskFinished((AiSceneAsset)asset, object),
 fileSystem);
 AssetTask_RunFileTask assetTask_RunFileTask =
 new AssetTask_RunFileTask(fileTask_LoadAiScene, asset);
 this->setTask(asset, assetTask_RunFileTask);
 assetTask_RunFileTask.execute();
 }

 void onFileTaskFinished(AiSceneAsset aiSceneAsset, void *object) {
 if (object instanceof AiScene) {
 aiSceneAsset.m_scene = (AiScene)object;
 this->onLoadingSucceeded(aiSceneAsset);
 } else {
 this->onLoadingFailed(aiSceneAsset);
 }
 }

 Asset createAsset(AssetPath assetPath, AssetManager.AssetParams assetParams) {
 return new AiSceneAsset(assetPath, this,
 (AiSceneAsset.AiSceneAssetParams)assetParams);
 }

 void destroyAsset(Asset var1) {}

 static class FileTask_LoadAiScene extends FileTask {
 std::string m_filename;
 EnumSet<AiPostProcessSteps> m_post_process_step_set;

 public
 FileTask_LoadAiScene(std::string_view string,
 EnumSet<AiPostProcessSteps> enumSet,
 IFileTaskCallback iFileTaskCallback,
 FileSystem fileSystem) {
 super(fileSystem, iFileTaskCallback);
 this->m_filename = string;
 this->m_post_process_step_set = enumSet;
 }

 std::string getErrorMessage() { return this->m_filename; }

 void done() {
 this->m_filename = nullptr;
 this->m_post_process_step_set = nullptr;
 }

 void *call() {
 return Jassimp.importFile(this->m_filename, this->m_post_process_step_set);
 }
 }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
