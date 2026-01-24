#include <string>
#include "zombie/asset/FileTask_LoadPackImage.h"

namespace zombie {
namespace asset {

FileTask_LoadPackImage::FileTask_LoadPackImage(const std::string& var1, const std::string& var2, FileSystem var3, IFileTaskCallback var4)
    : FileTask(var3, var4), m_pack_name(var1), m_image_name(var2), bMask(false), m_flags(0)
{
    // bMask and m_flags would be set using FileSystem methods if available
    // Example:
    // bMask = var3.getTexturePackAlpha(var1, var2);
    // m_flags = var3.getTexturePackFlags(var1);
}
}

void FileTask_LoadPackImage::done() {
    // No-op by default
}
}

void* FileTask_LoadPackImage::call() {
    // Wait for any pending file tasks (if needed)
        if (zombie::core::textures::TextureIDAssetManager::instance) {
            zombie::core::textures::TextureIDAssetManager::instance->waitFileTask();
        }

    if (!m_file_system) return nullptr;
    auto device = m_file_system->getTexturePackDevice(m_pack_name);
    if (!device) return nullptr;

    std::shared_ptr<ImageData> imageData;
    try {
        auto stream = m_file_system->openStream(device, m_image_name);
        if (stream) {
            imageData = std::make_shared<ImageData>(stream, bMask);
            if ((m_flags & 64) != 0) {
                imageData->initMipMaps();
            }
        }
    } catch (...) {
        // Optionally log error
        return nullptr;
    }
    return imageData.get(); // The caller is responsible for managing the returned pointer
}
}

} // namespace asset
} // namespace zombie
