#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace zombie {
namespace fileSystem {


class IFile {
public:
    virtual ~IFile() = default;
    bool open(const std::string& var1, int var2);

    void close();

    bool read(byte[] var1, long var2);

    bool write(byte[] var1, long var2);

   byte[] getBuffer();

    long size();

    bool seek(FileSeekMode var1, long var2);

    long pos();

    InputStream getInputStream();

    IFileDevice getDevice();

    void release();
}
} // namespace fileSystem
} // namespace zombie
