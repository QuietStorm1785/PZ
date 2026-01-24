#include "zombie/asset/AssetTask_RunFileTask.h"

namespace zombie {
namespace asset {

AssetTask_RunFileTask::AssetTask_RunFileTask(FileTask var1, Asset var2)
    : AssetTask(var2), m_file_task(var1), m_async_op(-1)
{
    // Constructor logic as per header
}
}

void AssetTask_RunFileTask::execute() {
    // FileSystem fs = m_asset.getAssetManager().getOwner().getFileSystem();
    // m_async_op = fs.runAsync(m_file_task);
}
}

void AssetTask_RunFileTask::cancel() {
    // FileSystem fs = m_asset.getAssetManager().getOwner().getFileSystem();
    // fs.cancelAsync(m_async_op);
    m_async_op = -1;
}
}

} // namespace asset
} // namespace zombie
