#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/vehicles/PolygonalMap2/PathFindRequest.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    PolygonalMap2 map;
    PathFindRequest request;
   static const ArrayDeque<PolygonalMap2$PathRequestTask> pool = std::make_unique<ArrayDeque<>>();

   private PolygonalMap2$PathRequestTask() {
   }

   PolygonalMap2$PathRequestTask init(PolygonalMap2 var1, PathFindRequest var2) {
      this.map = var1;
      this.request = var2;
    return this;
   }

    void execute() {
      if (this.request.dynamic_cast<IsoPlayer*>(mover) != nullptr) {
         this.map.requests.playerQ.push_back(this.request);
      } else if (this.request.dynamic_cast<IsoZombie*>(mover) != nullptr && ((IsoZombie)this.request.mover).target != nullptr) {
         this.map.requests.aggroZombieQ.push_back(this.request);
      } else {
         this.map.requests.otherQ.push_back(this.request);
      }
   }

   static PolygonalMap2$PathRequestTask alloc() {
      /* synchronized - TODO: add std::mutex */ (pool) {
         return pool.empty() ? new PolygonalMap2$PathRequestTask() : pool.pop();
      }
   }

    void release() {
      /* synchronized - TODO: add std::mutex */ (pool) {
         if (!$assertionsDisabled && pool.contains(this)) {
            throw std::make_unique<AssertionError>();
         } else {
            pool.push(this);
         }
      }
   }
}
} // namespace vehicles
} // namespace zombie
