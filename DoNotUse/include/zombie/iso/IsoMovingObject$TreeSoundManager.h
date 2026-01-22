#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/Audio.h"
#include "zombie/SoundManager.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/network/GameClient.h"
#include <algorithm>

namespace zombie {
namespace iso {


class IsoMovingObject {
public:
   private std::vector<IsoGridSquare> squares = std::make_unique<std::vector<>>();
   private long[] soundTime = new long[6];
   private Comparator<IsoGridSquare> comp = (var1, var2) -> {
    float var3 = this.getClosestListener(var1.x + 0.5F, var1.y + 0.5F, var1.z);
    float var4 = this.getClosestListener(var2.x + 0.5F, var2.y + 0.5F, var2.z);
      if (var3 > var4) {
    return 1;
      } else {
         return var3 < var4 ? -1 : 0;
      }
   };

    void addSquare(IsoGridSquare var1) {
      if (!this.squares.contains(var1)) {
         this.squares.push_back(var1);
      }
   }

    void update() {
      if (!this.squares.empty()) {
         Collections.sort(this.squares, this.comp);
    long var1 = System.currentTimeMillis();

         for (int var3 = 0; var3 < this.soundTime.length && var3 < this.squares.size(); var3++) {
    IsoGridSquare var4 = this.squares.get(var3);
            if (!(this.getClosestListener(var4.x + 0.5F, var4.y + 0.5F, var4.z) > 20.0F)) {
    int var5 = this.getFreeSoundSlot(var1);
               if (var5 == -1) {
                  break;
               }

    Audio var6 = nullptr;
    float var7 = 0.05F;
    float var8 = 16.0F;
    float var9 = 0.29999998F;
               if (GameClient.bClient) {
                  var6 = SoundManager.instance.PlayWorldSoundImpl("Bushes", false, var4.getX(), var4.getY(), var4.getZ(), var7, var8, var9, false);
               } else {
    BaseSoundEmitter var10 = IsoWorld.instance.getFreeEmitter(var4.x + 0.5F, var4.y + 0.5F, var4.z);
                  if (var10.playSound("Bushes") != 0L) {
                     this.soundTime[var5] = var1;
                  }
               }

               if (var6 != nullptr) {
                  this.soundTime[var5] = var1;
               }
            }
         }

         this.squares.clear();
      }
   }

    float getClosestListener(float var1, float var2, float var3) {
    float var4 = float.MAX_VALUE;

      for (int var5 = 0; var5 < IsoPlayer.numPlayers; var5++) {
    IsoPlayer var6 = IsoPlayer.players[var5];
         if (var6 != nullptr && var6.getCurrentSquare() != nullptr) {
    float var7 = var6.getX();
    float var8 = var6.getY();
    float var9 = var6.getZ();
    float var10 = IsoUtils.DistanceTo(var7, var8, var9 * 3.0F, var1, var2, var3 * 3.0F);
            if (var6.Traits.HardOfHearing.isSet()) {
               var10 *= 4.5F;
            }

            if (var10 < var4) {
               var4 = var10;
            }
         }
      }

    return var4;
   }

    int getFreeSoundSlot(long var1) {
    long var3 = int64_t.MAX_VALUE;
    int var5 = -1;

      for (int var6 = 0; var6 < this.soundTime.length; var6++) {
         if (this.soundTime[var6] < var3) {
            var3 = this.soundTime[var6];
            var5 = var6;
         }
      }

      return var1 - var3 < 1000L ? -1 : var5;
   }
}
} // namespace iso
} // namespace zombie
