#include <string>
#include "zombie/fileSystem/DiskFileDevice.h"

namespace zombie {
namespace fileSystem {


DiskFileDevice::DiskFileDevice(const std::string& var1)
    : m_root(var1) {}


IFile DiskFileDevice::createFile(IFile var1) {
    // Create a new DiskFile and return it
    auto file = std::make_shared<DiskFileDevice$DiskFile>(shared_from_this());
    return file;
}


void DiskFileDevice::destroyFile(IFile var1) {
    // Rely on smart pointer destruction
    var1.reset();
}


InputStream DiskFileDevice::createStream(const std::string& var1, InputStream var2) {
    // Create a new FileInputStream for the given path
    return std::make_shared<FileInputStream>(var1);
}


void DiskFileDevice::destroyStream(InputStream var1) {
    // Rely on smart pointer destruction
    var1.reset();
}


std::string DiskFileDevice::name() {
    return "DiskFileDevice";
}

} // namespace fileSystem
} // namespace zombie
