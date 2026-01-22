#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/fileSystem/FileSystem/TexturePackTextures.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace fileSystem {


class FileSystem {
public:
    static const int INVALID_ASYNC = -1;

   public abstract boolean mount(IFileDevice var1);

   public abstract boolean unMount(IFileDevice var1);

   public abstract IFile open(DeviceList var1, std::string var2, int var3);

   public abstract void close(IFile var1);

   public abstract int openAsync(DeviceList var1, std::string var2, int var3, IFileTask2Callback var4);

   public abstract void closeAsync(IFile var1, IFileTask2Callback var2);

   public abstract void cancelAsync(int var1);

   public abstract InputStream openStream(DeviceList var1, std::string var2) throws IOException;

   public abstract void closeStream(InputStream var1);

   public abstract int runAsync(FileTask var1);

   public abstract void updateAsyncTransactions();

   public abstract boolean hasWork();

   public abstract DeviceList getDefaultDevice();

   public abstract void mountTexturePack(std::string var1, TexturePackTextures var2, int var3);

   public abstract DeviceList getTexturePackDevice(std::string var1);

   public abstract int getTexturePackFlags(std::string var1);

   public abstract boolean getTexturePackAlpha(std::string var1, std::string var2);
}
} // namespace fileSystem
} // namespace zombie
