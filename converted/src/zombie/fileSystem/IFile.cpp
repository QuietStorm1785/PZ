#include "zombie/fileSystem/IFile.h"

namespace zombie {
namespace fileSystem {

bool IFile::open(const std::string &path, int mode) {
  // TODO: Implement open
  return false;
}

void IFile::close() {
  // TODO: Implement close
}

bool IFile::read(byte[] var1, long var2) {
  // TODO: Implement read
  return false;
}

bool IFile::write(byte[] var1, long var2) {
  // TODO: Implement write
  return false;
}

long IFile::size() {
  // TODO: Implement size
  return 0;
}

bool IFile::seek(FileSeekMode mode, long pos) {
  // TODO: Implement seek
  return false;
}

long IFile::pos() {
  // TODO: Implement pos
  return 0;
}

InputStream IFile::getInputStream() {
  // TODO: Implement getInputStream
  return nullptr;
}

IFileDevice IFile::getDevice() {
  // TODO: Implement getDevice
  return nullptr;
}

void IFile::release() {
  // TODO: Implement release
}

} // namespace fileSystem
} // namespace zombie
