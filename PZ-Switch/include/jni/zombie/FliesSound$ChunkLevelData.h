#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/FliesSound/FadeEmitter.h"
#include "zombie/characters/BodyDamage/BodyDamage.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/areas/IsoBuilding.h"

namespace zombie {


class FliesSound {
:
    int corpseCount;
   HashMap<IsoBuilding, Integer> buildingCorpseCount;
   int[] refCount;
   FadeEmitter[] emitters;

   FliesSound$ChunkLevelData(FliesSound var1) {
      this.this$0 = var1;
      this.corpseCount = 0;
      this.buildingCorpseCount = nullptr;
      this.refCount = new int[4];
      this.emitters = new FadeEmitter[4];
   }

    void corpseAdded(int var1, int var2, IsoBuilding var3) {
      if (var3 == nullptr) {
         this.corpseCount++;
      } else {
         if (this.buildingCorpseCount == nullptr) {
            this.buildingCorpseCount = std::make_unique<HashMap<>>();
         }

    int var4 = this.buildingCorpseCount.get(var3);
         if (var4 == nullptr) {
            this.buildingCorpseCount.put(var3, 1);
         } else {
            this.buildingCorpseCount.put(var3, var4 + 1);
         }
      }
   }

    void corpseRemoved(int var1, int var2, IsoBuilding var3) {
      if (var3 == nullptr) {
         this.corpseCount--;
      } else if (this.buildingCorpseCount != nullptr) {
    int var4 = this.buildingCorpseCount.get(var3);
         if (var4 != nullptr) {
            if (var4 > 1) {
               this.buildingCorpseCount.put(var3, var4 - 1);
            } else {
               this.buildingCorpseCount.remove(var3);
            }
         }
      }
   }

    IsoGridSquare calcSoundPos(int var1, int var2, int var3, IsoBuilding var4) {
    IsoChunk var5 = IsoWorld.instance.CurrentCell.getChunkForGridSquare(var1 * 10, var2 * 10, var3);
      if (var5 == nullptr) {
    return nullptr;
      } else {
    int var6 = 0;

         for (int var7 = 0; var7 < 10; var7++) {
            for (int var8 = 0; var8 < 10; var8++) {
    IsoGridSquare var9 = var5.getGridSquare(var8, var7, var3);
               if (var9 != nullptr && !var9.getStaticMovingObjects().isEmpty() && var9.getBuilding() == var4) {
                  FliesSound.tempSquares[var6++] = var9;
               }
            }
         }

         return var6 > 0 ? FliesSound.tempSquares[var6 / 2] : nullptr;
      }
   }

    void update(int var1, int var2, int var3, IsoPlayer var4) {
      this.refCount[var4.PlayerIndex]++;
    int var5 = this.this$0.getCorpseCount(var1, var2, var3, var4.getCurrentBuilding());
      if (BodyDamage.getSicknessFromCorpsesRate(var5) > ZomboidGlobals.FoodSicknessDecrease) {
    IsoBuilding var6 = var4.getCurrentBuilding();
    IsoGridSquare var7 = this.calcSoundPos(var1, var2, var3, var6);
         if (var7 == nullptr) {
            return;
         }

         if (this.emitters[var4.PlayerIndex] == nullptr) {
            this.emitters[var4.PlayerIndex] = new FadeEmitter(this.this$0);
         }

    FadeEmitter var8 = this.emitters[var4.PlayerIndex];
         if (var8.emitter == nullptr) {
            var8.emitter = IsoWorld.instance.getFreeEmitter(var7.x, var7.y, var3);
            var8.emitter.playSoundLoopedImpl("CorpseFlies");
            var8.emitter.setVolumeAll(0.0F);
            var8.volume = 0.0F;
            this.this$0.fadeEmitters.add(var8);
         } else {
            var8.sq.setHasFlies(false);
            var8.emitter.setPos(var7.x, var7.y, var3);
            if (var8.targetVolume != 1.0F && !this.this$0.fadeEmitters.contains(var8)) {
               this.this$0.fadeEmitters.add(var8);
            }
         }

         var8.targetVolume = 1.0F;
         var8.sq = var7;
         var7.setHasFlies(true);
      } else {
    FadeEmitter var9 = this.emitters[var4.PlayerIndex];
         if (var9 != nullptr && var9.emitter != nullptr) {
            if (!this.this$0.fadeEmitters.contains(var9)) {
               this.this$0.fadeEmitters.add(var9);
            }

            var9.targetVolume = 0.0F;
            var9.sq.setHasFlies(false);
         }
      }
   }

    void deref(IsoPlayer var1) {
    int var2 = var1.PlayerIndex;
      this.refCount[var2]--;
      if (this.refCount[var2] <= 0) {
         if (this.emitters[var2] != nullptr && this.emitters[var2].emitter != nullptr) {
            if (!this.this$0.fadeEmitters.contains(this.emitters[var2])) {
               this.this$0.fadeEmitters.add(this.emitters[var2]);
            }

            this.emitters[var2].targetVolume = 0.0F;
            this.emitters[var2].sq.setHasFlies(false);
         }
      }
   }

    void Reset() {
      this.corpseCount = 0;
      if (this.buildingCorpseCount != nullptr) {
         this.buildingCorpseCount.clear();
      }

      for (int var1 = 0; var1 < 4; var1++) {
         this.refCount[var1] = 0;
         if (this.emitters[var1] != nullptr) {
            this.emitters[var1].Reset();
         }
      }
   }
}
} // namespace zombie
