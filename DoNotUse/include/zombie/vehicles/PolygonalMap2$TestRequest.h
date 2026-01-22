#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/astar/Mover.h"
#include "zombie/vehicles/PolygonalMap2/IPathfinder.h"
#include "zombie/vehicles/PolygonalMap2/Path.h"

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    const Path path = std::make_shared<Path>();
    bool done;

   private PolygonalMap2$TestRequest() {
   }

    void Succeeded(Path var1, Mover var2) {
      this.path.copyFrom(var1);
      this.done = true;
   }

    void Failed(Mover var1) {
      this.path.clear();
      this.done = true;
   }
}
} // namespace vehicles
} // namespace zombie
