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


class IFileDevice {
public:
    virtual ~IFileDevice() = default;
    virtual IFile createFile(IFile file) = 0;
    virtual void destroyFile(IFile file) = 0;
    virtual InputStream createStream(const std::string& name, InputStream stream) = 0;
    virtual void destroyStream(InputStream stream) = 0;
    virtual std::string name() const = 0;
};
} // namespace fileSystem
} // namespace zombie
