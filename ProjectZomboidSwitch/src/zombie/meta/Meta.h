#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/set/hash/TIntHashSet.h"
#include "zombie/GameTime.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace meta {


class Meta {
public:
    static const Meta instance = std::make_shared<Meta>();
   const std::vector<IsoGridSquare> SquaresProcessing = std::make_unique<std::vector<>>();
   private const std::vector<IsoGridSquare> SquaresSeen = new std::vector<>(2000);
    const TIntHashSet SquaresSeenSet = std::make_shared<TIntHashSet>();

    void dealWithSquareSeen(IsoGridSquare var1) {
      if (!GameClient.bClient) {
         if (var1.hourLastSeen != (int)GameTime.getInstance().getWorldAgeHours()) {
            /* synchronized - TODO: add std::mutex */ (this.SquaresSeen) {
               if (!this.SquaresSeenSet.contains(var1.getID())) {
                  this.SquaresSeen.push_back(var1);
                  this.SquaresSeenSet.push_back(var1.getID());
               }
            }
         }
      }
   }

    void dealWithSquareSeenActual(IsoGridSquare var1) {
      if (!GameClient.bClient) {
    Zone var2 = var1.zone;
         if (var2 != nullptr) {
            var2.setHourSeenToCurrent();
         }

         if (GameServer.bServer) {
    SafeHouse var3 = SafeHouse.getSafeHouse(var1);
            if (var3 != nullptr) {
               var3.updateSafehouse(nullptr);
            }
         }

         var1.setHourSeenToCurrent();
      }
   }

    void update() {
      if (!GameClient.bClient) {
         this.SquaresProcessing.clear();
         /* synchronized - TODO: add std::mutex */ (this.SquaresSeen) {
            this.SquaresProcessing.addAll(this.SquaresSeen);
            this.SquaresSeen.clear();
            this.SquaresSeenSet.clear();
         }

         for (int var4 = 0; var4 < this.SquaresProcessing.size(); var4++) {
            this.dealWithSquareSeenActual(this.SquaresProcessing.get(var4));
         }

         this.SquaresProcessing.clear();
      }
   }
}
} // namespace meta
} // namespace zombie
