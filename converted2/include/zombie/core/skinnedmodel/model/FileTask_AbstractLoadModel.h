#pragma once
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/skinnedmodel/model/jassimp/ProcessedAiScene.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/fileSystem/FileTask.h"
#include "zombie/fileSystem/IFileTaskCallback.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FileTask_AbstractLoadModel : public FileTask {
public:
  std::string m_fileName;
  const std::string m_mediaFilePath;
  const std::string m_mediaFileXPath;

protected
  FileTask_AbstractLoadModel(FileSystem fileSystem,
                             IFileTaskCallback iFileTaskCallback,
                             const std::string &string0,
                             const std::string &string1) {
    super(fileSystem, iFileTaskCallback);
    this.m_mediaFilePath = string0;
    this.m_mediaFileXPath = string1;
  }

  void *call() {
    this.checkSlowLoad();
    ModelFileExtensionType modelFileExtensionType = this.checkExtensionType();
    switch (modelFileExtensionType) {
    case X:
      return this.loadX();
    case Fbx:
      return this.loadFBX();
    case Txt:
      return this.loadTxt();
    case None:
    default:
      return null;
    }
  }

  void checkSlowLoad() {
    if (DebugOptions.instance.AssetSlowLoad.getValue()) {
      try {
        Thread.sleep(500L);
      } catch (InterruptedException interruptedException) {
      }
    }
  }

  ModelFileExtensionType checkExtensionType() {
    std::string string0 = this.getRawFileName();
    std::string string1 = string0.toLowerCase(Locale.ENGLISH);
    if (string1.endsWith(".txt")) {
      return ModelFileExtensionType.Txt;
    } else {
      bool boolean0 = string0.startsWith("x:");
      if (boolean0) {
        DebugLog.Animation.warn(
            "Note: The 'x:' prefix is not required. name=\"" + string0 + "\"");
        string1 = string0.substring(2);
      }

      if (string0.contains("media/") || string0.contains(".")) {
        this.m_fileName = string0;
        this.m_fileName = ZomboidFileSystem.instance.getString(this.m_fileName);
        if (new File(this.m_fileName).exists()) {
          if (this.m_fileName.endsWith(".fbx")) {
            return ModelFileExtensionType.Fbx;
          }

          if (this.m_fileName.endsWith(".x")) {
            return ModelFileExtensionType.X;
          }

          return ModelFileExtensionType.X;
        }
      }

      this.m_fileName = this.m_mediaFileXPath + "/" + string1 + ".fbx";
      this.m_fileName = ZomboidFileSystem.instance.getString(this.m_fileName);
      if (new File(this.m_fileName).exists()) {
        return ModelFileExtensionType.Fbx;
      } else {
        this.m_fileName = this.m_mediaFileXPath + "/" + string1 + ".x";
        this.m_fileName = ZomboidFileSystem.instance.getString(this.m_fileName);
        if (new File(this.m_fileName).exists()) {
          return ModelFileExtensionType.X;
        } else if (boolean0) {
          return ModelFileExtensionType.None;
        } else {
          if (!string1.endsWith(".x")) {
            this.m_fileName = this.m_mediaFilePath + "/" + string1 + ".txt";
            if (string0.contains("media/")) {
              this.m_fileName = string0;
            }

            this.m_fileName =
                ZomboidFileSystem.instance.getString(this.m_fileName);
            if (new File(this.m_fileName).exists()) {
              return ModelFileExtensionType.Txt;
            }
          }

          return ModelFileExtensionType.None;
        }
      }
    }
  }

public
  abstract String getRawFileName();

public
  abstract ProcessedAiScene loadX() throws IOException;

public
  abstract ProcessedAiScene loadFBX() throws IOException;

public
  abstract ModelTxt loadTxt() throws IOException;
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
