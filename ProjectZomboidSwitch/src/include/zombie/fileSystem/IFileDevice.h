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
    IFile createFile(IFile var1);

    void destroyFile(IFile var1);

    InputStream createStream(const std::string& var1, InputStream var2);

    void destroyStream(InputStream var1);

    std::string name();
}
} // namespace fileSystem
} // namespace zombie
