#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/ImageData.h"
#include "zombie/core/textures/TextureIDAssetManager.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/fileSystem/FileTask.h"
#include "zombie/fileSystem/IFileTaskCallback.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace asset {


class FileTask_LoadImageData : public FileTask {
public:
    std::string m_image_name;
    bool bMask = false;

    public FileTask_LoadImageData(const std::string& var1, FileSystem var2, IFileTaskCallback var3) {
      super(var2, var3);
      this.m_image_name = var1;
   }

    std::string getErrorMessage() {
      return this.m_image_name;
   }

    void done() {
   }

    void* call() {
      TextureIDAssetManager.instance.waitFileTask();
      if (DebugOptions.instance.AssetSlowLoad.getValue()) {
         try {
            Thread.sleep(500L);
         } catch (InterruptedException var9) {
         }
      }

    ImageData var3;
      try (
    FileInputStream var1 = new FileInputStream(this.m_image_name);
    BufferedInputStream var2 = new BufferedInputStream(var1);
      ) {
         var3 = new ImageData(var2, this.bMask);
      }

    return var3;
   }
}
} // namespace asset
} // namespace zombie
