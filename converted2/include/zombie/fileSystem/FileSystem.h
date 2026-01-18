#pragma once
#include "zombie/core/textures/TexturePackPage.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
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
  abstract boolean mount(IFileDevice device);

public
  abstract boolean unMount(IFileDevice device);

public
  abstract IFile open(DeviceList deviceList, String path, int mode);

public
  abstract void close(IFile file);

public
  abstract int openAsync(DeviceList deviceList, String path, int mode,
                         IFileTask2Callback cb);

public
  abstract void closeAsync(IFile file, IFileTask2Callback cb);

public
  abstract void cancelAsync(int id);

public
  abstract InputStream openStream(DeviceList deviceList,
                                  String path) throws IOException;

public
  abstract void closeStream(InputStream stream);

public
  abstract int runAsync(FileTask task);

public
  abstract void updateAsyncTransactions();

public
  abstract boolean hasWork();

public
  abstract DeviceList getDefaultDevice();

public
  abstract void mountTexturePack(String name,
                                 FileSystem.TexturePackTextures subTextures,
                                 int flags);

public
  abstract DeviceList getTexturePackDevice(String name);

public
  abstract int getTexturePackFlags(String name);

public
  abstract boolean getTexturePackAlpha(String name, String page);

public
  static final class SubTexture {
    std::string m_pack_name;
    std::string m_page_name;
  public
    TexturePackPage.SubTextureInfo m_info;

  public
    SubTexture(const std::string &packName, const std::string &pageName,
               TexturePackPage.SubTextureInfo info) {
      this.m_pack_name = packName;
      this.m_page_name = pageName;
      this.m_info = info;
    }
  }

  public static final class TexturePackTextures extends
      HashMap<String, FileSystem.SubTexture> {
  }
}
} // namespace fileSystem
} // namespace zombie
