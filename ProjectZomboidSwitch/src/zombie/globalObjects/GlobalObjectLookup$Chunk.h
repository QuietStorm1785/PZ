#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace globalObjects {


class GlobalObjectLookup {
public:
   const std::vector<GlobalObject> objects = std::make_unique<std::vector<>>();

   private GlobalObjectLookup$Chunk() {
   }

    void Reset() {
      this.objects.clear();
   }
}
} // namespace globalObjects
} // namespace zombie
