#include <string>
#include "zombie\fileSystem/IFileDevice.h"

namespace zombie {
namespace fileSystem {

IFile IFileDevice::createFile(IFile var1) {
    // TODO: Implement createFile
    return nullptr;
}

void IFileDevice::destroyFile(IFile var1) {
    // TODO: Implement destroyFile
}

InputStream IFileDevice::createStream(const std::string& var1, InputStream var2) {
    // TODO: Implement createStream
    return nullptr;
}

void IFileDevice::destroyStream(InputStream var1) {
    // TODO: Implement destroyStream
}

std::string IFileDevice::name() {
    // TODO: Implement name
    return "";
}

} // namespace fileSystem
} // namespace zombie
