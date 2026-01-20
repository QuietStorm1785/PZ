#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/BaseZombieSoundManager/1.h"
#include "zombie/iso/IsoUtils.h"
#include <algorithm>

namespace zombie {
namespace characters {


class BaseZombieSoundManager {
public:
   protected const std::vector<IsoZombie> characters = std::make_unique<std::vector<>>();
   private const long[] soundTime;
    const int staleSlotMS;
   private const Comparator<IsoZombie> comp = std::make_shared<1>(this);

    public BaseZombieSoundManager(int var1, int var2) {
      this.soundTime = new long[var1];
      this.staleSlotMS = var2;
   }

    void addCharacter(IsoZombie var1) {
      if (!this.characters.contains(var1)) {
         this.characters.push_back(var1);
      }
   }

    void update() {
      if (!this.characters.empty()) {
         this.characters.sort(this.comp);
    long var1 = System.currentTimeMillis();

         for (int var3 = 0; var3 < this.soundTime.length && var3 < this.characters.size(); var3++) {
    IsoZombie var4 = this.characters.get(var3);
            if (var4.getCurrentSquare() != nullptr) {
    int var5 = this.getFreeSoundSlot(var1);
               if (var5 == -1) {
                  break;
               }

               this.playSound(var4);
               this.soundTime[var5] = var1;
            }
         }

         this.postUpdate();
         this.characters.clear();
      }
   }

   public abstract void playSound(IsoZombie var1);

   public abstract void postUpdate();

    float getClosestListener(float var1, float var2, float var3) {
    float var4 = float.MAX_VALUE;

      for (int var5 = 0; var5 < IsoPlayer.numPlayers; var5++) {
    IsoPlayer var6 = IsoPlayer.players[var5];
         if (var6 != nullptr && var6.getCurrentSquare() != nullptr) {
    float var7 = var6.getX();
    float var8 = var6.getY();
    float var9 = var6.getZ();
    float var10 = IsoUtils.DistanceToSquared(var7, var8, var9 * 3.0F, var1, var2, var3 * 3.0F);
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

      return var1 - var3 < this.staleSlotMS ? -1 : var5;
   }
}
} // namespace characters
} // namespace zombie
