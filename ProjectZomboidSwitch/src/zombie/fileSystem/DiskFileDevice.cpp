#include <string>
#include "zombie\fileSystem/DiskFileDevice.h"

namespace zombie {
namespace fileSystem {

public DiskFileDevice::DiskFileDevice(const std::string& var1) {
    // TODO: Implement DiskFileDevice
    return nullptr;
}

IFile DiskFileDevice::createFile(IFile var1) {
    // TODO: Implement createFile
    return nullptr;
}

void DiskFileDevice::destroyFile(IFile var1) {
    // TODO: Implement destroyFile
}

InputStream DiskFileDevice::createStream(const std::string& var1, InputStream var2) {
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

} // namespace fileSystem
} // namespace zombie
