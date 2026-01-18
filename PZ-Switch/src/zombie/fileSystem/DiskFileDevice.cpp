#include "zombie/fileSystem/DiskFileDevice.h"

namespace zombie {
namespace fileSystem {

public
DiskFileDevice::DiskFileDevice(const std::string &string) {
 // TODO: Implement DiskFileDevice
 return nullptr;
}

IFile DiskFileDevice::createFile(IFile iFile) {
 // TODO: Implement createFile
 return nullptr;
}

void DiskFileDevice::destroyFile(IFile var1) {
 // TODO: Implement destroyFile
}

InputStream DiskFileDevice::createStream(const std::string &string,
 InputStream var2) {
 // TODO: Implement createStream
 return nullptr;
}

void DiskFileDevice::destroyStream(InputStream var1) {
 // TODO: Implement destroyStream
}

std::string DiskFileDevice::name() {
 // TODO: Implement name
 return "";
}

bool DiskFileDevice::open(const std::string &string, int int0) {
 // TODO: Implement open
 return false;
}

void DiskFileDevice::close() {
 // TODO: Implement close
}

bool DiskFileDevice::read(byte[] bytes, long long0) {
 // TODO: Implement read
 return false;
}

bool DiskFileDevice::write(byte[] bytes, long long0) {
 // TODO: Implement write
 return false;
}

long DiskFileDevice::size() {
 // TODO: Implement size
 return 0;
}

bool DiskFileDevice::seek(FileSeekMode fileSeekMode, long long0) {
 // TODO: Implement seek
 return false;
}

long DiskFileDevice::pos() {
 // TODO: Implement pos
 return 0;
}

InputStream DiskFileDevice::getInputStream() {
 // TODO: Implement getInputStream
 return nullptr;
}

IFileDevice DiskFileDevice::getDevice() {
 // TODO: Implement getDevice
 return nullptr;
}

void DiskFileDevice::release() {
 // TODO: Implement release
}

} // namespace fileSystem
} // namespace zombie
