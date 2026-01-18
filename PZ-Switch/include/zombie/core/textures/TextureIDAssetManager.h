#pragma once
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/asset/AssetTask_RunFileTask.h"
#include "zombie/asset/FileTask_LoadImageData.h"
#include "zombie/asset/FileTask_LoadPackImage.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/utils/DirectBufferAllocator.h"
#include "zombie/fileSystem/FileSystem.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace textures {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class TextureIDAssetManager : public AssetManager {
public:
 static const TextureIDAssetManager instance = new TextureIDAssetManager();

 void startLoading(Asset asset) {
 TextureID textureID = (TextureID)asset;
 FileSystem fileSystem = this->getOwner().getFileSystem();
 if (textureID.assetParams != nullptr &&
 textureID.assetParams.subTexture != nullptr) {
 FileSystem.SubTexture subTexture = textureID.assetParams.subTexture;
 FileTask_LoadPackImage fileTask_LoadPackImage =
 new FileTask_LoadPackImage(
 subTexture.m_pack_name, subTexture.m_page_name, fileSystem,
 object->this->onFileTaskFinished(asset, object);
 fileTask_LoadPackImage.setPriority(7);
 AssetTask_RunFileTask assetTask_RunFileTask0 =
 new AssetTask_RunFileTask(fileTask_LoadPackImage, asset);
 this->setTask(asset, assetTask_RunFileTask0);
 assetTask_RunFileTask0.execute();
 } else {
 FileTask_LoadImageData fileTask_LoadImageData =
 new FileTask_LoadImageData(
 asset.getPath().getPath(), fileSystem,
 object->this->onFileTaskFinished(asset, object);
 fileTask_LoadImageData.setPriority(7);
 AssetTask_RunFileTask assetTask_RunFileTask1 =
 new AssetTask_RunFileTask(fileTask_LoadImageData, asset);
 this->setTask(asset, assetTask_RunFileTask1);
 assetTask_RunFileTask1.execute();
 }
 }

 void unloadData(Asset asset) {
 TextureID textureID = (TextureID)asset;
 if (!textureID.isDestroyed()) {
 RenderThread.invokeOnRenderContext(textureID::destroy);
 }
 }

 Asset createAsset(AssetPath assetPath, AssetManager.AssetParams assetParams) {
 return new TextureID(assetPath, this,
 (TextureID.TextureIDAssetParams)assetParams);
 }

 void destroyAsset(Asset var1) {}

 void onFileTaskFinished(Asset asset, void *object) {
 TextureID textureID = (TextureID)asset;
 if (object instanceof ImageData) {
 textureID.setImageData((ImageData)object);
 this->onLoadingSucceeded(asset);
 } else {
 this->onLoadingFailed(asset);
 }
 }

 void waitFileTask() {
 while (DirectBufferAllocator.getBytesAllocated() > 52428800L) {
 try {
 Thread.sleep(20L);
 } catch (InterruptedException interruptedException) {
 }
 }
 }
}
} // namespace textures
} // namespace core
} // namespace zombie
