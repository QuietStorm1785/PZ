#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/asset/Asset/State.h"
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/fileSystem/IFile.h"
#include "zombie/fileSystem/IFileTask2Callback.h"

namespace zombie {
namespace asset {


class AssetTask_LoadFromFileAsync :  AssetTask {
:
    int m_async_op = -1;
    bool bStream;

   AssetTask_LoadFromFileAsync(Asset var1, boolean var2) {
      super(var1);
      this.bStream = var2;
   }

    void execute() {
    FileSystem var1 = this.m_asset.getAssetManager().getOwner().getFileSystem();
    int var2 = 4 | (this.bStream ? 16 : 1);
      this.m_async_op = var1.openAsync(var1.getDefaultDevice(), this.m_asset.getPath().m_path, var2, this);
   }

    void cancel() {
    FileSystem var1 = this.m_asset.getAssetManager().getOwner().getFileSystem();
      var1.cancelAsync(this.m_async_op);
      this.m_async_op = -1;
   }

    void onFileTaskFinished(IFile var1, void* var2) {
      this.m_async_op = -1;
      if (this.m_asset.m_priv.m_desired_state == State.READY) {
         if (var2 != Boolean.TRUE) {
            this.m_asset.m_priv.onLoadingFailed();
         } else if (!this.m_asset.getAssetManager().loadDataFromFile(this.m_asset, var1)) {
            this.m_asset.m_priv.onLoadingFailed();
         } else {
            this.m_asset.m_priv.onLoadingSucceeded();
         }
      }
   }
}
} // namespace asset
} // namespace zombie
