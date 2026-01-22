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
   BEGIN,
   END,
   CURRENT;
}
} // namespace fileSystem
} // namespace zombie
