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

    public FileTask_LoadPackImage(const std::string& var1, const std::string& var2, FileSystem var3, IFileTaskCallback var4) {
      super(var3, var4);
      this.m_pack_name = var1;
      this.m_image_name = var2;
      this.bMask = var3.getTexturePackAlpha(var1, var2);
      this.m_flags = var3.getTexturePackFlags(var1);
   }

    void done() {
   }

    void* call() {
      TextureIDAssetManager.instance.waitFileTask();
    DeviceList var1 = this.m_file_system.getTexturePackDevice(this.m_pack_name);

    ImageData var4;
      try (InputStream var2 = this.m_file_system.openStream(var1, this.m_image_name)) {
    auto var3 = std::make_shared<ImageData>(var2, this.bMask);
         if ((this.m_flags & 64) != 0) {
            var3.initMipMaps();
         }

         var4 = var3;
      }

    return var4;
   }
}
} // namespace asset
} // namespace zombie
