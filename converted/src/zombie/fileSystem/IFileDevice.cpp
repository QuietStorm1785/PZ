#include "zombie/fileSystem/IFileDevice.h"

namespace zombie {
namespace fileSystem {

IFile IFileDevice::createFile(IFile child) {
 // TODO: Implement createFile
 return nullptr;
}

void IFileDevice::destroyFile(IFile file) {
 // TODO: Implement destroyFile
}

InputStream IFileDevice::createStream(const std::string& path, InputStream child) {
 // TODO: Implement createStream
 return nullptr;
}

void IFileDevice::destroyStream(InputStream stream) {
 // TODO: Implement destroyStream
}

std::string IFileDevice::name() {
 // TODO: Implement name
 return "";
}

} // namespace fileSystem
} // namespace zombie
