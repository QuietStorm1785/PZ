#pragma once
#include "zombie/core/textures/TexturePackPage.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace fileSystem {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FileSystem {
public:
 static const int INVALID_ASYNC = -1;

public
 boolean mount(IFileDevice device);

public
 boolean unMount(IFileDevice device);

public
 IFile open(DeviceList deviceList, String path, int mode);

public
 void close(IFile file);

public
 int openAsync(DeviceList deviceList, String path, int mode,
 IFileTask2Callback cb);

public
 void closeAsync(IFile file, IFileTask2Callback cb);

public
 void cancelAsync(int id);

public
 InputStream openStream(DeviceList deviceList,
 String path) throws IOException;

public
 void closeStream(InputStream stream);

public
 int runAsync(FileTask task);

public
 void updateAsyncTransactions();

public
 boolean hasWork();

public
 DeviceList getDefaultDevice();

public
 void mountTexturePack(String name,
 FileSystem.TexturePackTextures subTextures,
 int flags);

public
 DeviceList getTexturePackDevice(String name);

public
 int getTexturePackFlags(String name);

public
 boolean getTexturePackAlpha(String name, String page);

public
 static class SubTexture {
 std::string m_pack_name;
 std::string m_page_name;
 public
 TexturePackPage.SubTextureInfo m_info;

 public
 SubTexture(std::string_view packName, std::string_view pageName,
 TexturePackPage.SubTextureInfo info) {
 this->m_pack_name = packName;
 this->m_page_name = pageName;
 this->m_info = info;
 }
 }

 public static class TexturePackTextures extends
 HashMap<String, FileSystem.SubTexture> {
 }
}
} // namespace fileSystem
} // namespace zombie
