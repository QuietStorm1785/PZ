#include <string>
#include "zombie/fileSystem/IFile.h"

namespace zombie {
namespace fileSystem {

bool IFile::open(const std::string& var1, int var2) {
    // Interface stub: should be overridden by subclass
    return false;
}

void IFile::close() {
    // Interface stub: should be overridden by subclass
}

bool IFile::read(byte[] var1, long var2) {
    // Interface stub: should be overridden by subclass
    return false;
}

bool IFile::write(byte[] var1, long var2) {
    // Interface stub: should be overridden by subclass
    return false;
}

long IFile::size() {
    // Interface stub: should be overridden by subclass
    return 0;
}

bool IFile::seek(FileSeekMode var1, long var2) {
    // Interface stub: should be overridden by subclass
    return false;
}

long IFile::pos() {
    // Interface stub: should be overridden by subclass
    return 0;
}

InputStream IFile::getInputStream() {
    // Interface stub: should be overridden by subclass
    return nullptr;
}

IFileDevice IFile::getDevice() {
    // Interface stub: should be overridden by subclass
    return nullptr;
}

void IFile::release() {
    // Interface stub: should be overridden by subclass
}

} // namespace fileSystem
} // namespace zombie
