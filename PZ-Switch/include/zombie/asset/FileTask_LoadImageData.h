#pragma once
#include "zombie/core/textures/ImageData.h"
#include "zombie/core/textures/TextureIDAssetManager.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/fileSystem/FileTask.h"
#include "zombie/fileSystem/IFileTaskCallback.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace asset {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FileTask_LoadImageData : public FileTask {
public:
 std::string m_image_name;
 bool bMask = false;

public
 FileTask_LoadImageData(const std::string &string, FileSystem fileSystem,
 IFileTaskCallback iFileTaskCallback) {
 super(fileSystem, iFileTaskCallback);
 this->m_image_name = string;
 }

 std::string getErrorMessage() { return this->m_image_name; }

 void done() {}

 void *call() {
 TextureIDAssetManager.instance.waitFileTask();
 if (DebugOptions.instance.AssetSlowLoad.getValue()) {
 try {
 Thread.sleep(500L);
 } catch (InterruptedException interruptedException) {
 }
 }

 ImageData imageData;
 try(FileInputStream fileInputStream =
 new FileInputStream(this->m_image_name);
 BufferedInputStream bufferedInputStream =
 new BufferedInputStream(fileInputStream);) {
 imageData = new ImageData(bufferedInputStream, this->bMask);
 }

 return imageData;
 }
}
} // namespace asset
} // namespace zombie
