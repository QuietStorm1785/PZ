#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace fileSystem {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IFile {
public:
 virtual ~IFile() = default;
 bool open(const std::string &path, int mode);

 void close();

 bool read(byte[] var1, long var2);

 bool write(byte[] var1, long var2);

 byte[] getBuffer();

 long size();

 bool seek(FileSeekMode mode, long pos);

 long pos();

 InputStream getInputStream();

 IFileDevice getDevice();

 void release();
}
} // namespace fileSystem
} // namespace zombie
