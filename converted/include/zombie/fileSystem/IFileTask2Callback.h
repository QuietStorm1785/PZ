#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace fileSystem {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IFileTask2Callback {
public:
  virtual ~IFileTask2Callback() = default;
  void onFileTaskFinished(IFile file, void *result);
}
} // namespace fileSystem
} // namespace zombie
