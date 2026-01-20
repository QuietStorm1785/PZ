#include <string>
#include "zombie\fileSystem/MemoryFileDevice$MemoryFile.h"

namespace zombie {
namespace fileSystem {

bool MemoryFileDevice$MemoryFile::open(const std::string& var1, int var2) {
    // TODO: Implement open
    return false;
}

void MemoryFileDevice$MemoryFile::close() {
    // TODO: Implement close
}

bool MemoryFileDevice$MemoryFile::read(byte[] var1, long var2) {
    // TODO: Implement read
    return false;
}

bool MemoryFileDevice$MemoryFile::write(byte[] var1, long var2) {
    // TODO: Implement write
    return false;
}

long MemoryFileDevice$MemoryFile::size() {
    // TODO: Implement size
    return 0;
}

bool MemoryFileDevice$MemoryFile::seek(FileSeekMode var1, long var2) {
    // TODO: Implement seek
    return false;
}

long MemoryFileDevice$MemoryFile::pos() {
    // TODO: Implement pos
    return 0;
}

InputStream MemoryFileDevice$MemoryFile::getInputStream() {
    // TODO: Implement getInputStream
    return nullptr;
}

IFileDevice MemoryFileDevice$MemoryFile::getDevice() {
    // TODO: Implement getDevice
    return nullptr;
}

void MemoryFileDevice$MemoryFile::release() {
    // TODO: Implement release
}

} // namespace fileSystem
} // namespace zombie
