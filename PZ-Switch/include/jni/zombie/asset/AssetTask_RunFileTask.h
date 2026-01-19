#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/fileSystem/FileTask.h"

namespace zombie {
namespace asset {


class AssetTask_RunFileTask :  AssetTask {
:
    const FileTask m_file_task;
    int m_async_op = -1;

     AssetTask_RunFileTask(FileTask var1, Asset var2) {
      super(var2);
      this.m_file_task = var1;
   }

    void execute() {
    FileSystem var1 = this.m_asset.getAssetManager().getOwner().getFileSystem();
      this.m_async_op = var1.runAsync(this.m_file_task);
   }

    void cancel() {
    FileSystem var1 = this.m_asset.getAssetManager().getOwner().getFileSystem();
      var1.cancelAsync(this.m_async_op);
      this.m_async_op = -1;
   }
}
} // namespace asset
} // namespace zombie
