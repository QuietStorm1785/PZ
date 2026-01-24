#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/procedure/TIntObjectProcedure.h"
#include "zombie/vehicles/PolygonalMap2/Node.h"
#include "zombie/vehicles/PolygonalMap2/SearchNode.h"
#include "AstarCpp/VGAStar.h"

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
   PolygonalMap2$VGAStar$InitProc(VGAStar var1) {
      this.this$0 = var1;
   }

    bool execute(int var1, Node var2) {
    SearchNode var3 = SearchNode.alloc().init(this.this$0, var2);
      var3.square = var2.square;
      this.this$0.squareToNode.put(var1, var3);
      this.this$0.nodeMap.put(var2.ID, var3);
      this.this$0.searchNodes.push_back(var3);
    return true;
   }
}
} // namespace vehicles
} // namespace zombie
