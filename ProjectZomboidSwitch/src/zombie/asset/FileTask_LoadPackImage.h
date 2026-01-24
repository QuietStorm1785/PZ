#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/ImageData.h"
#include "zombie/core/textures/TextureIDAssetManager.h"
#include "zombie/fileSystem/DeviceList.h"
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/fileSystem/FileTask.h"
#include "zombie/fileSystem/IFileTaskCallback.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace asset {


class FileTask_LoadPackImage : public FileTask {
public:
    std::string m_pack_name;
    std::string m_image_name;
    bool bMask;
    int m_flags;

    FileTask_LoadPackImage(const std::string& pack_name,
                          const std::string& image_name,
                          std::shared_ptr<FileSystem> fs,
                          std::shared_ptr<IFileTaskCallback> callback)
        : FileTask(fs, callback),
          m_pack_name(pack_name),
          m_image_name(image_name),
          bMask(fs->getTexturePackAlpha(pack_name, image_name)),
          m_flags(fs->getTexturePackFlags(pack_name)) {}

    void done() override {}

    void* call() override;
};
} // namespace asset
} // namespace zombie
