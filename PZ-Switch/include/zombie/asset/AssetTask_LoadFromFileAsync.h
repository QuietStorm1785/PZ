#pragma once
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/fileSystem/IFile.h"
#include "zombie/fileSystem/IFileTask2Callback.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace asset {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AssetTask_LoadFromFileAsync : public AssetTask {
public:
 int m_async_op = -1;
 bool bStream;

 AssetTask_LoadFromFileAsync(Asset asset, boolean boolean0) {
 super(asset);
 this->bStream = boolean0;
 }

 void execute() {
 FileSystem fileSystem =
 this->m_asset.getAssetManager().getOwner().getFileSystem();
 int int0 = 4 | (this->bStream ? 16 : 1);
 this->m_async_op =
 fileSystem.openAsync(fileSystem.getDefaultDevice(),
 this->m_asset.getPath().m_path, int0, this);
 }

 void cancel() {
 FileSystem fileSystem =
 this->m_asset.getAssetManager().getOwner().getFileSystem();
 fileSystem.cancelAsync(this->m_async_op);
 this->m_async_op = -1;
 }

 void onFileTaskFinished(IFile iFile, void *object) {
 this->m_async_op = -1;
 if (this->m_asset.m_priv.m_desired_state == Asset.State.READY) {
 if (object != Boolean.TRUE) {
 this->m_asset.m_priv.onLoadingFailed();
 } else if (!this->m_asset.getAssetManager().loadDataFromFile(this->m_asset,
 iFile) {
 this->m_asset.m_priv.onLoadingFailed();
 } else {
 this->m_asset.m_priv.onLoadingSucceeded();
 }
 }
 }
}
} // namespace asset
} // namespace zombie
