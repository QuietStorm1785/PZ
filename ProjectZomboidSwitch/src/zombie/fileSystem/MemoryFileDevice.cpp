#include <string>
#include "zombie\fileSystem/MemoryFileDevice.h"

namespace zombie {
namespace fileSystem {

IFile MemoryFileDevice::createFile(IFile var1) {
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

} // namespace fileSystem
} // namespace zombie
