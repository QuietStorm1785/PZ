#include <string>
#include "zombie/fileSystem/MemoryFileDevice.h"

namespace zombie {
namespace fileSystem {

IFile MemoryFileDevice::createFile(IFile var1) {
    // Create a new MemoryFile and return it
    auto file = std::make_shared<MemoryFile>(shared_from_this());
    return file;
}

void MemoryFileDevice::destroyFile(IFile var1) {
    // Rely on smart pointer destruction
    var1.reset();
}

InputStream MemoryFileDevice::createStream(const std::string& var1, InputStream var2) {
    // Not supported for memory device
    return nullptr;
}

void MemoryFileDevice::destroyStream(InputStream var1) {
    // Rely on smart pointer destruction
    var1.reset();
}

std::string MemoryFileDevice::name() {
    return "MemoryFileDevice";
}

} // namespace fileSystem
} // namespace zombie
