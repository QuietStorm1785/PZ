#include <string>
#include "zombie\fileSystem/FileSystemImpl.h"

namespace zombie {
namespace fileSystem {

public FileSystemImpl::FileSystemImpl() {
    // TODO: Implement FileSystemImpl
    return nullptr;
}

bool FileSystemImpl::mount(IFileDevice var1) {
    // TODO: Implement mount
    return false;
}

bool FileSystemImpl::unMount(IFileDevice var1) {
    // TODO: Implement unMount
    return false;
}

IFile FileSystemImpl::open(DeviceList var1, const std::string& var2, int var3) {
    // TODO: Implement open
    return nullptr;
}

void FileSystemImpl::close(IFile var1) {
    // TODO: Implement close
}

int FileSystemImpl::openAsync(DeviceList var1, const std::string& var2, int var3, IFileTask2Callback var4) {
    // TODO: Implement openAsync
    return 0;
}

void FileSystemImpl::closeAsync(IFile var1, IFileTask2Callback var2) {
    // TODO: Implement closeAsync
}

void FileSystemImpl::cancelAsync(int var1) {
    // TODO: Implement cancelAsync
}

InputStream FileSystemImpl::openStream(DeviceList var1, const std::string& var2) {
    // TODO: Implement openStream
    return nullptr;
}

void FileSystemImpl::closeStream(InputStream var1) {
    // TODO: Implement closeStream
}

int FileSystemImpl::runAsync(AsyncItem var1) {
    // TODO: Implement runAsync
    return 0;
}

int FileSystemImpl::runAsync(FileTask var1) {
    // TODO: Implement runAsync
    return 0;
}

void FileSystemImpl::updateAsyncTransactions() {
    // TODO: Implement updateAsyncTransactions
}

bool FileSystemImpl::hasWork() {
    // TODO: Implement hasWork
    return false;
}

DeviceList FileSystemImpl::getDefaultDevice() {
    // TODO: Implement getDefaultDevice
    return nullptr;
}

void FileSystemImpl::mountTexturePack(const std::string& var1, TexturePackTextures var2, int var3) {
    // TODO: Implement mountTexturePack
}

DeviceList FileSystemImpl::getTexturePackDevice(const std::string& var1) {
    // TODO: Implement getTexturePackDevice
    return nullptr;
}

int FileSystemImpl::getTexturePackFlags(const std::string& var1) {
    // TODO: Implement getTexturePackFlags
    return 0;
}

bool FileSystemImpl::getTexturePackAlpha(const std::string& var1, const std::string& var2) {
    // TODO: Implement getTexturePackAlpha
    return false;
}

} // namespace fileSystem
} // namespace zombie
