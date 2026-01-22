#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/PolygonalMap2/PathFindRequest.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
   const ArrayDeque<PathFindRequest> playerQ = std::make_unique<ArrayDeque<>>();
   const ArrayDeque<PathFindRequest> aggroZombieQ = std::make_unique<ArrayDeque<>>();
   const ArrayDeque<PathFindRequest> otherQ = std::make_unique<ArrayDeque<>>();

   private PolygonalMap2$RequestQueue() {
   }

    bool isEmpty() {
      return this.playerQ.empty() && this.aggroZombieQ.empty() && this.otherQ.empty();
   }

    PathFindRequest removeFirst() {
      if (!this.playerQ.empty()) {
         return this.playerQ.removeFirst();
      } else {
         return !this.aggroZombieQ.empty() ? this.aggroZombieQ.removeFirst() : this.otherQ.removeFirst();
      }
   }

    PathFindRequest removeLast() {
      if (!this.otherQ.empty()) {
         return this.otherQ.removeLast();
      } else {
         return !this.aggroZombieQ.empty() ? this.aggroZombieQ.removeLast() : this.playerQ.removeLast();
      }
   }
}
} // namespace vehicles
} // namespace zombie
