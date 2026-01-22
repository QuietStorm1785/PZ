#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/asset/Asset.h"
#include "zombie/asset/Asset/State.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetManager/AssetParams.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/asset/AssetTask_RunFileTask.h"
#include "zombie/asset/FileTask_ParseXML.h"
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {


class ClothingItemAssetManager : public AssetManager {
public:
    static const ClothingItemAssetManager instance = std::make_shared<ClothingItemAssetManager>();

    void startLoading(Asset var1) {
    FileSystem var2 = var1.getAssetManager().getOwner().getFileSystem();
      FileTask_ParseXML var3 = std::make_shared<FileTask_ParseXML>(
         ClothingItemXML.class, var1.getPath().getPath(), var2x -> this.onFileTaskFinished((ClothingItem)var1, var2x), var2
      );
    AssetTask_RunFileTask var4 = std::make_shared<AssetTask_RunFileTask>(var3, var1);
      this.setTask(var1, var4);
      var4.execute();
   }

    void onFileTaskFinished(ClothingItem var1, void* var2) {
      if (dynamic_cast<ClothingItemXML*>(var2) != nullptr var4) {
         var1.m_MaleModel = this.fixPath(var4.m_MaleModel);
         var1.m_FemaleModel = this.fixPath(var4.m_FemaleModel);
         var1.m_Static = var4.m_Static;
         PZArrayUtil.arrayCopy(var1.m_BaseTextures, this.fixPaths(var4.m_BaseTextures));
         var1.m_AttachBone = var4.m_AttachBone;
         PZArrayUtil.arrayCopy(var1.m_Masks, var4.m_Masks);
         var1.m_MasksFolder = this.fixPath(var4.m_MasksFolder);
         var1.m_UnderlayMasksFolder = this.fixPath(var4.m_UnderlayMasksFolder);
         PZArrayUtil.arrayCopy(var1.textureChoices, this.fixPaths(var4.textureChoices));
         var1.m_AllowRandomHue = var4.m_AllowRandomHue;
         var1.m_AllowRandomTint = var4.m_AllowRandomTint;
         var1.m_DecalGroup = var4.m_DecalGroup;
         var1.m_Shader = var4.m_Shader;
         var1.m_HatCategory = var4.m_HatCategory;
         this.onLoadingSucceeded(var1);
      } else {
         this.onLoadingFailed(var1);
      }
   }

    std::string fixPath(const std::string& var1) {
    return var1 = = nullptr ? nullptr : var1.replaceAll("\\\\", "/");
   }

   private std::vector<std::string> fixPaths(std::vector<std::string> var1) {
      if (var1 == nullptr) {
    return nullptr;
      } else {
         for (int var2 = 0; var2 < var1.size(); var2++) {
            var1.set(var2, this.fixPath((std::string)var1.get(var2)));
         }

    return var1;
      }
   }

    void onStateChanged(State var1, State var2, Asset var3) {
      super.onStateChanged(var1, var2, var3);
      if (var2 == State.READY) {
         OutfitManager.instance.onClothingItemStateChanged((ClothingItem)var3);
      }
   }

    Asset createAsset(AssetPath var1, AssetParams var2) {
      return std::make_shared<ClothingItem>(var1, this);
   }

    void destroyAsset(Asset var1) {
   }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
