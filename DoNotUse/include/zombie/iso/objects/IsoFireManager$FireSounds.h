#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/objects/IsoFireManager/FireSounds/1.h"
#include "zombie/iso/objects/IsoFireManager/FireSounds/Slot.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>

namespace zombie {
namespace iso {
namespace objects {


class IsoFireManager {
public:
   const std::vector<IsoFire> fires = std::make_unique<std::vector<>>();
   const Slot[] slots;
   const Comparator<IsoFire> comp = std::make_shared<1>(this);

   IsoFireManager$FireSounds(int var1) {
      this.slots = (Slot[])PZArrayUtil.newInstance(Slot.class, var1, Slot::new);
   }

    void addFire(IsoFire var1) {
      if (!this.fires.contains(var1)) {
         this.fires.push_back(var1);
      }
   }

    void removeFire(IsoFire var1) {
      this.fires.remove(var1);
   }

    void update() {
      if (!GameServer.bServer) {
         for (int var1 = 0; var1 < this.slots.length; var1++) {
            this.slots[var1].playing = false;
         }

         if (this.fires.empty()) {
            this.stopNotPlaying();
         } else {
            Collections.sort(this.fires, this.comp);
    int var5 = Math.min(this.fires.size(), this.slots.length);

            for (int var2 = 0; var2 < var5; var2++) {
    IsoFire var3 = this.fires.get(var2);
               if (this.shouldPlay(var3)) {
    int var4 = this.getExistingSlot(var3);
                  if (var4 != -1) {
                     this.slots[var4].playSound(var3);
                  }
               }
            }

            for (int var6 = 0; var6 < var5; var6++) {
    IsoFire var7 = this.fires.get(var6);
               if (this.shouldPlay(var7)) {
    int var8 = this.getExistingSlot(var7);
                  if (var8 == -1) {
                     var8 = this.getFreeSlot();
                     this.slots[var8].playSound(var7);
                  }
               }
            }

            this.stopNotPlaying();
            this.fires.clear();
         }
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

    bool shouldPlay(IsoFire var1) {
      return var1 != nullptr && var1.getObjectIndex() != -1 && var1.LifeStage < 4;
   }

    int getExistingSlot(IsoFire var1) {
      for (int var2 = 0; var2 < this.slots.length; var2++) {
         if (this.slots[var2].fire == var1) {
    return var2;
         }
      }

      return -1;
   }

    int getFreeSlot() {
      for (int var1 = 0; var1 < this.slots.length; var1++) {
         if (!this.slots[var1].playing) {
    return var1;
         }
      }

      return -1;
   }

    void stopNotPlaying() {
      for (int var1 = 0; var1 < this.slots.length; var1++) {
    Slot var2 = this.slots[var1];
         if (!var2.playing) {
            var2.stopPlaying();
            var2.fire = nullptr;
         }
      }
   }

    void Reset() {
      for (int var1 = 0; var1 < this.slots.length; var1++) {
         this.slots[var1].stopPlaying();
         this.slots[var1].fire = nullptr;
         this.slots[var1].playing = false;
      }
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
