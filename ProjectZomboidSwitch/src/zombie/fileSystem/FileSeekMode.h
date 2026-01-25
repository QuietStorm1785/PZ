#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace fileSystem {

enum class FileSeekMode {
   Begin = 0,
   Current = 1,
   End = 2
};
} // namespace fileSystem
} // namespace zombie
