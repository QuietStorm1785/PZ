#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/URI.h"
#include "zombie/PredicatedFileWatcher.h"
#include "zombie/PredicatedFileWatcher/IPredicatedFileWatcherCallback.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/skinnedmodel/ModelManager/ModAnimations.h"
#include "zombie/core/skinnedmodel/model/AnimationAsset.h"
#include "zombie/core/skinnedmodel/model/AnimationAsset/AnimationAssetParams.h"
#include "zombie/core/skinnedmodel/model/AnimationAssetManager.h"
#include "zombie/core/skinnedmodel/model/ModelMesh.h"
#include "zombie/debug/DebugLog.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace skinnedmodel {


class ModelManager {
public:
    URI m_baseURI;
    URI m_mediaURI;
    std::string m_dir;
    std::string m_dirSecondary;
    std::string m_dirAbsolute;
    std::string m_dirSecondaryAbsolute;
    ModelMesh m_animationsModel;
    ModAnimations m_modAnimations;

   public ModelManager$AnimDirReloader(ModelManager var1, URI var2, URI var3, std::string var4, ModelMesh var5, ModAnimations var6) {
      this.this$0 = var1;
      var4 = ZomboidFileSystem.instance.getRelativeFile(var2, var4);
      this.m_baseURI = var2;
      this.m_mediaURI = var3;
      this.m_dir = ZomboidFileSystem.instance.normalizeFolderPath(var4);
      this.m_dirAbsolute = ZomboidFileSystem.instance.normalizeFolderPath(std::make_shared<File>(std::make_shared<File>(this.m_baseURI), this.m_dir));
      if (this.m_dir.contains("/anims/")) {
         this.m_dirSecondary = this.m_dir.replace("/anims/", "/anims_X/");
         this.m_dirSecondaryAbsolute = ZomboidFileSystem.instance.normalizeFolderPath(std::make_shared<File>(std::make_shared<File>(this.m_baseURI), this.m_dirSecondary));
      }

      this.m_animationsModel = var5;
      this.m_modAnimations = var6;
   }

    bool IsInDir(const std::string& var1) {
      var1 = ZomboidFileSystem.instance.normalizeFolderPath(var1);

      try {
         return this.m_dirSecondary == nullptr
            ? var1.startsWith(this.m_dirAbsolute)
            : var1.startsWith(this.m_dirAbsolute) || var1.startsWith(this.m_dirSecondaryAbsolute);
      } catch (Exception var3) {
         var3.printStackTrace();
    return false;
      }
   }

    void call(const std::string& var1) {
    std::string var2 = var1.toLowerCase();
      if (var2.endsWith(".fbx") || var2.endsWith(".x") || var2.endsWith(".txt")) {
    std::string var3 = ZomboidFileSystem.instance.getAnimName(this.m_mediaURI, std::make_shared<File>(var1));
    AnimationAsset var4 = this.this$0.getAnimationAsset(var3);
         if (var4 != nullptr) {
            if (!var4.empty()) {
               DebugLog.General.debugln("Reloading animation: %s", this.this$0.animAssetToString(var4));
               if (!$assertionsDisabled && var4.getRefCount() != 1) {
                  throw std::make_unique<AssertionError>();
               }

    AnimationAssetParams var5 = std::make_shared<AnimationAssetParams>();
               var5.animationsMesh = this.m_animationsModel;
               AnimationAssetManager.instance.reload(var4, var5);
            }
         } else {
            this.this$0.loadAnim(var3, this.m_animationsModel, this.m_modAnimations);
         }
      }
   }

    PredicatedFileWatcher GetFileWatcher() {
      return std::make_shared<PredicatedFileWatcher>(this.m_dir, this::IsInDir, this);
   }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
