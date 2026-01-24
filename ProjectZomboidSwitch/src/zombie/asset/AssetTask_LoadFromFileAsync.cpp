#include "zombie/asset/AssetTask_LoadFromFileAsync.h"

namespace zombie {
namespace asset {

void AssetTask_LoadFromFileAsync::execute() {
    // FileSystem fs = m_asset.getAssetManager().getOwner().getFileSystem();
    // int flags = 4 | (bStream ? 16 : 1);
    // m_async_op = fs.openAsync(fs.getDefaultDevice(), m_asset.getPath().m_path, flags, this);
}

void AssetTask_LoadFromFileAsync::cancel() {
    // FileSystem fs = m_asset.getAssetManager().getOwner().getFileSystem();
    // fs.cancelAsync(m_async_op);
    m_async_op = -1;
}

void AssetTask_LoadFromFileAsync::onFileTaskFinished(IFile var1, void* var2) {
    m_async_op = -1;
    if (m_asset.m_priv->m_desired_state == State::READY) {
        if (var2 != reinterpret_cast<void*>(true)) {
            m_asset.m_priv->onLoadingFailed();
        } else if (!m_asset.getAssetManager().loadDataFromFile(m_asset, var1)) {
            m_asset.m_priv->onLoadingFailed();
        } else {
            m_asset.m_priv->onLoadingSucceeded();
        }
    }
}

} // namespace asset
} // namespace zombie
