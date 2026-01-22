#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {

enum class IsoChunk {
   Solid,
   WallN,
   WallW,
   WallS,
   WallE,
   Tree,
   Floor;
}
} // namespace iso
} // namespace zombie
