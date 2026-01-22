#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/skinnedmodel/model/FileTask_AbstractLoadModel/1.h"
#include "zombie/core/skinnedmodel/model/jassimp/ProcessedAiScene.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/fileSystem/FileTask.h"
#include "zombie/fileSystem/IFileTaskCallback.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class FileTask_AbstractLoadModel : public FileTask {
public:
    std::string m_fileName;
    const std::string m_mediaFilePath;
    const std::string m_mediaFileXPath;

    protected FileTask_AbstractLoadModel(FileSystem var1, IFileTaskCallback var2, const std::string& var3, const std::string& var4) {
      super(var1, var2);
      this.m_mediaFilePath = var3;
      this.m_mediaFileXPath = var4;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void* call() {
      this.checkSlowLoad();
    ModelFileExtensionType var1 = this.checkExtensionType();
      switch (1.$SwitchMap$zombie$core$skinnedmodel$model$ModelFileExtensionType[var1.ordinal()]) {
         case 1:
            return this.loadX();
         case 2:
            return this.loadFBX();
         case 3:
            return this.loadTxt();
         case 4:
         default:
    return nullptr;
      }
   }

    void checkSlowLoad() {
      if (DebugOptions.instance.AssetSlowLoad.getValue()) {
         try {
            Thread.sleep(500L);
         } catch (InterruptedException var2) {
         }
      }
   }

    ModelFileExtensionType checkExtensionType() {
    std::string var1 = this.getRawFileName();
    std::string var2 = var1.toLowerCase(Locale.ENGLISH);
      if (var2.endsWith(".txt")) {
         return ModelFileExtensionType.Txt;
      } else {
    bool var3 = var1.startsWith("x:");
         if (var3) {
            DebugLog.Animation.warn("Note: The 'x:' prefix is not required. name=\"" + var1 + "\"");
            var2 = var1.substr(2);
         }

         if (var1.contains("media/") || var1.contains(".")) {
            this.m_fileName = var1;
            this.m_fileName = ZomboidFileSystem.instance.getString(this.m_fileName);
            if (std::make_shared<File>(this.m_fileName).exists()) {
               if (this.m_fileName.endsWith(".fbx")) {
                  return ModelFileExtensionType.Fbx;
               }

               if (this.m_fileName.endsWith(".x")) {
                  return ModelFileExtensionType.X;
               }

               return ModelFileExtensionType.X;
            }
         }

         this.m_fileName = this.m_mediaFileXPath + "/" + var2 + ".fbx";
         this.m_fileName = ZomboidFileSystem.instance.getString(this.m_fileName);
         if (std::make_shared<File>(this.m_fileName).exists()) {
            return ModelFileExtensionType.Fbx;
         } else {
            this.m_fileName = this.m_mediaFileXPath + "/" + var2 + ".x";
            this.m_fileName = ZomboidFileSystem.instance.getString(this.m_fileName);
            if (std::make_shared<File>(this.m_fileName).exists()) {
               return ModelFileExtensionType.X;
            } else if (var3) {
               return ModelFileExtensionType.None;
            } else {
               if (!var2.endsWith(".x")) {
                  this.m_fileName = this.m_mediaFilePath + "/" + var2 + ".txt";
                  if (var1.contains("media/")) {
                     this.m_fileName = var1;
                  }

                  this.m_fileName = ZomboidFileSystem.instance.getString(this.m_fileName);
                  if (std::make_shared<File>(this.m_fileName).exists()) {
                     return ModelFileExtensionType.Txt;
                  }
               }

               return ModelFileExtensionType.None;
            }
         }
      }
   }

   public abstract std::string getRawFileName();

   public abstract ProcessedAiScene loadX() throws IOException;

   public abstract ProcessedAiScene loadFBX() throws IOException;

   public abstract ModelTxt loadTxt() throws IOException;
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
