#include "zombie/fileSystem/MemoryFileDevice.h"

namespace zombie {
namespace fileSystem {

IFile MemoryFileDevice::createFile(IFile iFile) {
 // TODO: Implement createFile
 return nullptr;
}

void MemoryFileDevice::destroyFile(IFile var1) {
 // TODO: Implement destroyFile
}

InputStream MemoryFileDevice::createStream(const std::string& var1, InputStream var2) {
 // TODO: Implement createStream
 return nullptr;
}

void MemoryFileDevice::destroyStream(InputStream var1) {
 // TODO: Implement destroyStream
}

std::string MemoryFileDevice::name() {
 // TODO: Implement name
 return "";
}

bool MemoryFileDevice::open(const std::string& string, int int0) {
 // TODO: Implement open
 return false;
}

void MemoryFileDevice::close() {
 // TODO: Implement close
}

bool MemoryFileDevice::read(byte[] bytes, long long1) {
 // TODO: Implement read
 return false;
}

bool MemoryFileDevice::write(byte[] bytes, long long3) {
 // TODO: Implement write
 return false;
}

long MemoryFileDevice::size() {
 // TODO: Implement size
 return 0;
}

bool MemoryFileDevice::seek(FileSeekMode fileSeekMode, long long0) {
 // TODO: Implement seek
 return false;
}

long MemoryFileDevice::pos() {
 // TODO: Implement pos
 return 0;
}

InputStream MemoryFileDevice::getInputStream() {
 // TODO: Implement getInputStream
 return nullptr;
}

IFileDevice MemoryFileDevice::getDevice() {
 // TODO: Implement getDevice
 return nullptr;
}

void MemoryFileDevice::release() {
 // TODO: Implement release
}

} // namespace fileSystem
} // namespace zombie
