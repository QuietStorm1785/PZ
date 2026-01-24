#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetManager/AssetParams.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/asset/AssetTask_RunFileTask.h"
#include "zombie/asset/FileTask_LoadImageData.h"
#include "zombie/asset/FileTask_LoadPackImage.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/textures/TextureID/TextureIDAssetParams.h"
#include "zombie/core/utils/DirectBufferAllocator.h"
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/fileSystem/FileSystem/SubTexture.h"

namespace zombie {
namespace core {
namespace textures {


class TextureIDAssetManager : public AssetManager {
public:
   static std::shared_ptr<TextureIDAssetManager> instance;

    void startLoading(Asset var1) {
    TextureID var2 = (TextureID)var1;
    FileSystem var3 = this.getOwner().getFileSystem();
      if (var2.assetParams != nullptr && var2.assetParams.subTexture != nullptr) {
    SubTexture var7 = var2.assetParams.subTexture;
    FileTask_LoadPackImage var8 = std::make_shared<FileTask_LoadPackImage>(var7.m_pack_name, var7.m_page_name, var3, var2x -> this.onFileTaskFinished(var1, var2x));
         var8.setPriority(7);
    AssetTask_RunFileTask var6 = std::make_shared<AssetTask_RunFileTask>(var8, var1);
         this.setTask(var1, var6);
         var6.execute();
      } else {
    FileTask_LoadImageData var4 = std::make_shared<FileTask_LoadImageData>(var1.getPath().getPath(), var3, var2x -> this.onFileTaskFinished(var1, var2x));
         var4.setPriority(7);
    AssetTask_RunFileTask var5 = std::make_shared<AssetTask_RunFileTask>(var4, var1);
         this.setTask(var1, var5);
         var5.execute();
      }
   }

    void unloadData(Asset var1) {
    TextureID var2 = (TextureID)var1;
      if (!var2.isDestroyed()) {
         RenderThread.invokeOnRenderContext(var2::destroy);
      }
   }

    Asset createAsset(AssetPath var1, AssetParams var2) {
      return std::make_shared<TextureID>(var1, this, (TextureIDAssetParams)var2);
   }

    void destroyAsset(Asset var1) {
   }

    void onFileTaskFinished(Asset var1, void* var2) {
    TextureID var3 = (TextureID)var1;
      if (dynamic_cast<ImageData*>(var2) != nullptr) {
         var3.setImageData((ImageData)var2);
         this.onLoadingSucceeded(var1);
      } else {
         this.onLoadingFailed(var1);
      }
   }

    void waitFileTask() {
      while (DirectBufferAllocator.getBytesAllocated() > 52428800L) {
         try {
            Thread.sleep(20L);
         } catch (InterruptedException var2) {
         }
      }
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
