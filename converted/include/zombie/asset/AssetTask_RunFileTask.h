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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class AssetTask_RunFileTask : public AssetTask {
public:
 const FileTask m_file_task;
 int m_async_op = -1;

 public AssetTask_RunFileTask(FileTask fileTask, Asset asset) {
 super(asset);
 this->m_file_task = fileTask;
 }

 void execute() {
 FileSystem fileSystem = this->m_asset.getAssetManager().getOwner().getFileSystem();
 this->m_async_op = fileSystem.runAsync(this->m_file_task);
 }

 void cancel() {
 FileSystem fileSystem = this->m_asset.getAssetManager().getOwner().getFileSystem();
 fileSystem.cancelAsync(this->m_async_op);
 this->m_async_op = -1;
 }
}
} // namespace asset
} // namespace zombie
