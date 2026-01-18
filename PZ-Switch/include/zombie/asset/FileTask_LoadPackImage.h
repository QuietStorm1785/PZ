#pragma once
#include "zombie/core/textures/ImageData.h"
#include "zombie/core/textures/TextureIDAssetManager.h"
#include "zombie/fileSystem/DeviceList.h"
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

class FileTask_LoadPackImage : public FileTask {
public:
 std::string m_pack_name;
 std::string m_image_name;
 bool bMask;
 int m_flags;

public
 FileTask_LoadPackImage(const std::string &string0, const std::string &string1,
 FileSystem fileSystem,
 IFileTaskCallback iFileTaskCallback) {
 super(fileSystem, iFileTaskCallback);
 this->m_pack_name = string0;
 this->m_image_name = string1;
 this->bMask = fileSystem.getTexturePackAlpha(string0, string1);
 this->m_flags = fileSystem.getTexturePackFlags(string0);
 }

 void done() {}

 void *call() {
 TextureIDAssetManager.instance.waitFileTask();
 DeviceList deviceList =
 this->m_file_system.getTexturePackDevice(this->m_pack_name);

 ImageData imageData0;
 try(InputStream inputStream =
 this->m_file_system.openStream(deviceList, this->m_image_name) {
 ImageData imageData1 = new ImageData(inputStream, this->bMask);
 if ((this->m_flags & 64) != 0) {
 imageData1.initMipMaps();
 }

 imageData0 = imageData1;
 }

 return imageData0;
 }
}
} // namespace asset
} // namespace zombie
