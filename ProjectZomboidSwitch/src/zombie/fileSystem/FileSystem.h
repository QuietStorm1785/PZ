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
    static constexpr int INVALID_ASYNC = -1;
    virtual ~FileSystem() = default;

    virtual bool mount(std::shared_ptr<IFileDevice> device) = 0;
    virtual bool unMount(std::shared_ptr<IFileDevice> device) = 0;
    virtual std::shared_ptr<IFile> open(std::shared_ptr<DeviceList> devices, const std::string& path, int mode) = 0;
    virtual void close(std::shared_ptr<IFile> file) = 0;
    virtual int openAsync(std::shared_ptr<DeviceList> devices, const std::string& path, int mode, std::shared_ptr<IFileTask2Callback> cb) = 0;
    virtual void closeAsync(std::shared_ptr<IFile> file, std::shared_ptr<IFileTask2Callback> cb) = 0;
    virtual void cancelAsync(int id) = 0;
    virtual std::shared_ptr<InputStream> openStream(std::shared_ptr<DeviceList> devices, const std::string& path) = 0;
    virtual void closeStream(std::shared_ptr<InputStream> stream) = 0;
    virtual int runAsync(std::shared_ptr<FileTask> task) = 0;
    virtual void updateAsyncTransactions() = 0;
    virtual bool hasWork() const = 0;
    virtual std::shared_ptr<DeviceList> getDefaultDevice() const = 0;
    virtual void mountTexturePack(const std::string& name, std::shared_ptr<TexturePackTextures> textures, int flags) = 0;
    virtual std::shared_ptr<DeviceList> getTexturePackDevice(const std::string& name) const = 0;
    virtual int getTexturePackFlags(const std::string& name) const = 0;
    virtual bool getTexturePackAlpha(const std::string& name, const std::string& page) const = 0;
};
} // namespace fileSystem
} // namespace zombie
