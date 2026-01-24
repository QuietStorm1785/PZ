#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/array/TFloatArrayList.h"
#include "zombie/ai/KnownBlockedEdges.h"
#include "AstarCpp/Mover.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/PolygonalMap2/IPathfinder.h"
#include "zombie/vehicles/PolygonalMap2/Path.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    IPathfinder finder;
    Mover mover;
    bool bCanCrawl;
    bool bIgnoreCrawlCost;
    bool bCanThump;
   const std::vector<KnownBlockedEdges> knownBlockedEdges = std::make_unique<std::vector<>>();
    float startX;
    float startY;
    float startZ;
    float targetX;
    float targetY;
    float targetZ;
    const TFloatArrayList targetXYZ = std::make_shared<TFloatArrayList>();
    const Path path = std::make_shared<Path>();
    bool cancel = false;
   static const ArrayDeque<PolygonalMap2$PathFindRequest> pool = std::make_unique<ArrayDeque<>>();

   PolygonalMap2$PathFindRequest init(IPathfinder var1, Mover var2, float var3, float var4, float var5, float var6, float var7, float var8) {
      this.finder = var1;
      this.mover = var2;
      this.bCanCrawl = false;
      this.bIgnoreCrawlCost = false;
      this.bCanThump = false;
    IsoZombie var9 = (IsoZombie)Type.tryCastTo(var2, IsoZombie.class);
      if (var9 != nullptr) {
         this.bCanCrawl = var9.isCrawling() || var9.isCanCrawlUnderVehicle();
         this.bIgnoreCrawlCost = var9.isCrawling() && !var9.isCanWalk();
         this.bCanThump = true;
      }

      this.startX = var3;
      this.startY = var4;
      this.startZ = var5;
      this.targetX = var6;
      this.targetY = var7;
      this.targetZ = var8;
      this.targetXYZ.resetQuick();
      this.path.clear();
      this.cancel = false;
    IsoGameCharacter var10 = (IsoGameCharacter)Type.tryCastTo(var2, IsoGameCharacter.class);
      if (var10 != nullptr) {
    std::vector var11 = var10.getMapKnowledge().getKnownBlockedEdges();

         for (int var12 = 0; var12 < var11.size(); var12++) {
    KnownBlockedEdges var13 = (KnownBlockedEdges)var11.get(var12);
            this.knownBlockedEdges.push_back(KnownBlockedEdges.alloc().init(var13));
         }
      }

    return this;
   }

    void addTargetXYZ(float var1, float var2, float var3) {
      this.targetXYZ.push_back(var1);
      this.targetXYZ.push_back(var2);
      this.targetXYZ.push_back(var3);
   }

   static PolygonalMap2$PathFindRequest alloc() {
      return pool.empty() ? new PolygonalMap2$PathFindRequest() : pool.pop();
   }

    void release() {
      KnownBlockedEdges.releaseAll(this.knownBlockedEdges);
      this.knownBlockedEdges.clear();
      if (!$assertionsDisabled && pool.contains(this)) {
         throw std::make_unique<AssertionError>();
      } else {
         pool.push(this);
      }
   }
}
} // namespace vehicles
} // namespace zombie
