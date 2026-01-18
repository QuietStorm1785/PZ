#include "zombie/fileSystem/FileSystemImpl.h"

namespace zombie {
namespace fileSystem {

public
FileSystemImpl::FileSystemImpl() {
 // TODO: Implement FileSystemImpl
 return nullptr;
}

bool FileSystemImpl::mount(IFileDevice var1) {
 // TODO: Implement mount
 return false;
}

bool FileSystemImpl::unMount(IFileDevice iFileDevice) {
 // TODO: Implement unMount
 return false;
}

IFile FileSystemImpl::open(DeviceList deviceList, const std::string &string,
 int int0) {
 // TODO: Implement open
 return nullptr;
}

void FileSystemImpl::close(IFile iFile) {
 // TODO: Implement close
}

int FileSystemImpl::openAsync(DeviceList deviceList, const std::string &string,
 int int0, IFileTask2Callback iFileTask2Callback) {
 // TODO: Implement openAsync
 return 0;
}

void FileSystemImpl::closeAsync(IFile iFile,
 IFileTask2Callback iFileTask2Callback) {
 // TODO: Implement closeAsync
}

void FileSystemImpl::cancelAsync(int int0) {
 // TODO: Implement cancelAsync
}

InputStream FileSystemImpl::openStream(DeviceList deviceList,
 const std::string &string) {
 // TODO: Implement openStream
 return nullptr;
}

void FileSystemImpl::closeStream(InputStream var1) {
 // TODO: Implement closeStream
}

int FileSystemImpl::runAsync(FileSystemImpl.AsyncItem asyncItem) {
 // TODO: Implement runAsync
 return 0;
}

int FileSystemImpl::runAsync(FileTask fileTask) {
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

void FileSystemImpl::mountTexturePack(
 const std::string &string,
 FileSystem.TexturePackTextures texturePackTextures, int int0) {
 // TODO: Implement mountTexturePack
}

DeviceList FileSystemImpl::getTexturePackDevice(const std::string &string) {
 // TODO: Implement getTexturePackDevice
 return nullptr;
}

int FileSystemImpl::getTexturePackFlags(const std::string &string) {
 // TODO: Implement getTexturePackFlags
 return 0;
}

bool FileSystemImpl::getTexturePackAlpha(const std::string &string1,
 const std::string &string0) {
 // TODO: Implement getTexturePackAlpha
 return false;
}

void *FileSystemImpl::call() {
 // TODO: Implement call
 return nullptr;
}

void FileSystemImpl::handleResult(void *object) {
 // TODO: Implement handleResult
}

void FileSystemImpl::done() {
 // TODO: Implement done
}

void *FileSystemImpl::call() {
 // TODO: Implement call
 return nullptr;
}

void FileSystemImpl::handleResult(void *object) {
 // TODO: Implement handleResult
}

void FileSystemImpl::done() {
 // TODO: Implement done
}

} // namespace fileSystem
} // namespace zombie
