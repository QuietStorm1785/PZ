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


class MemoryFileDevice : public std::enable_shared_from_this<MemoryFileDevice> {
public:
      MemoryFileDevice() = default;

      IFile createFile(IFile var1);
      void destroyFile(IFile var1);
      InputStream createStream(const std::string& var1, InputStream var2);
      void destroyStream(InputStream var1);
      std::string name() const;
};
} // namespace fileSystem
} // namespace zombie
