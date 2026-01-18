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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IFileDevice {
public:
 virtual ~IFileDevice() = default;
 IFile createFile(IFile child);

 void destroyFile(IFile file);

 InputStream createStream(const std::string& path, InputStream child);

 void destroyStream(InputStream stream);

 std::string name();
}
} // namespace fileSystem
} // namespace zombie
