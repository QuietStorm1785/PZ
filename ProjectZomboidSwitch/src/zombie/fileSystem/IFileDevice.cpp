#include <string>
#include "zombie/fileSystem/IFileDevice.h"

namespace zombie {
namespace fileSystem {

IFile IFileDevice::createFile(IFile var1) {
    // Interface stub: should be overridden by subclass
    return nullptr;
}

void IFileDevice::destroyFile(IFile var1) {
    // Interface stub: should be overridden by subclass
}

InputStream IFileDevice::createStream(const std::string& var1, InputStream var2) {
    // Interface stub: should be overridden by subclass
    return nullptr;
}

void IFileDevice::destroyStream(InputStream var1) {
    // Interface stub: should be overridden by subclass
}

std::string IFileDevice::name() {
    // Interface stub: should be overridden by subclass
    return "";
}

} // namespace fileSystem
} // namespace zombie
