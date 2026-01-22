#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/fileSystem/MemoryFileDevice/MemoryFile.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace fileSystem {


class MemoryFileDevice {
public:
    IFile createFile(IFile var1) {
      return std::make_shared<MemoryFile>(var1, this);
   }

    void destroyFile(IFile var1) {
   }

    InputStream createStream(const std::string& var1, InputStream var2) {
    return nullptr;
   }

    void destroyStream(InputStream var1) {
   }

    std::string name() {
      return "memory";
   }
}
} // namespace fileSystem
} // namespace zombie
