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
    virtual bool open(const std::string& path, int mode) = 0;
    virtual void close() = 0;
    virtual bool read(uint8_t* buffer, int64_t length) = 0;
    virtual bool write(const uint8_t* buffer, int64_t length) = 0;
    virtual int64_t size() const = 0;
    virtual bool seek(FileSeekMode mode, int64_t offset) = 0;
    virtual int64_t pos() const = 0;
    virtual InputStream getInputStream() = 0;
    virtual IFileDevice getDevice() = 0;
    virtual void release() = 0;
};
} // namespace fileSystem
} // namespace zombie
