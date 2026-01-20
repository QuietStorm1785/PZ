#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/procedure/TObjectProcedure.h"
#include "zombie/vehicles/PolygonalMap2/Node.h"

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
   PolygonalMap2$1(PolygonalMap2 var1) {
      this.this$0 = var1;
   }

    bool execute(Node var1) {
      var1.release();
    return true;
   }
}
} // namespace vehicles
} // namespace zombie
