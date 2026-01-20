#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/ZombieVocalsManager/1.h"
#include "zombie/characters/ZombieVocalsManager/ObjectWithDistance.h"
#include "zombie/characters/ZombieVocalsManager/Slot.h"
#include "zombie/core/Core.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/network/GameServer.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>

namespace zombie {
namespace characters {


class ZombieVocalsManager {
public:
    static const ZombieVocalsManager instance = std::make_shared<ZombieVocalsManager>();
   private const std::unordered_set<IsoZombie> m_added = std::make_unique<std::unordered_set<>>();
   private const ObjectPool<ObjectWithDistance> m_objectPool = std::make_shared<ObjectPool>(ObjectWithDistance::new);
   private const std::vector<ObjectWithDistance> m_objects = std::make_unique<std::vector<>>();
   private const Slot[] m_slots;
    long m_updateMS = 0L;
   private const Comparator<ObjectWithDistance> comp = std::make_shared<1>(this);

    public ZombieVocalsManager() {
    uint8_t var1 = 20;
      this.m_slots = (Slot[])PZArrayUtil.newInstance(Slot.class, var1, Slot::new);
   }

    void addCharacter(IsoZombie var1) {
      if (!this.m_added.contains(var1)) {
         this.m_added.push_back(var1);
    ObjectWithDistance var2 = (ObjectWithDistance)this.m_objectPool.alloc();
         var2.character = var1;
         this.m_objects.push_back(var2);
      }
   }

    void update() {
      if (!GameServer.bServer) {
    long var1 = System.currentTimeMillis();
         if (var1 - this.m_updateMS >= 500L) {
            this.m_updateMS = var1;

            for (int var3 = 0; var3 < this.m_slots.length; var3++) {
               this.m_slots[var3].playing = false;
            }

            if (this.m_objects.empty()) {
               this.stopNotPlaying();
            } else {
               for (int var7 = 0; var7 < this.m_objects.size(); var7++) {
    ObjectWithDistance var4 = this.m_objects.get(var7);
    IsoZombie var5 = var4.character;
                  var4.distSq = this.getClosestListener(var5.x, var5.y, var5.z);
               }

               this.m_objects.sort(this.comp);
    int var8 = PZMath.min(this.m_slots.length, this.m_objects.size());

               for (int var9 = 0; var9 < var8; var9++) {
    IsoZombie var11 = this.m_objects.get(var9).character;
                  if (this.shouldPlay(var11)) {
    int var6 = this.getExistingSlot(var11);
                     if (var6 != -1) {
                        this.m_slots[var6].playSound(var11);
                     }
                  }
               }

               for (int var10 = 0; var10 < var8; var10++) {
    IsoZombie var12 = this.m_objects.get(var10).character;
                  if (this.shouldPlay(var12)) {
    int var13 = this.getExistingSlot(var12);
                     if (var13 == -1) {
                        var13 = this.getFreeSlot();
                        this.m_slots[var13].playSound(var12);
                     }
                  }
               }

               this.stopNotPlaying();
               this.postUpdate();
               this.m_added.clear();
               this.m_objectPool.release(this.m_objects);
               this.m_objects.clear();
            }
         }
      }
   }

    bool shouldPlay(IsoZombie var1) {
      return var1.getCurrentSquare() != nullptr;
   }

    int getExistingSlot(IsoZombie var1) {
      for (int var2 = 0; var2 < this.m_slots.length; var2++) {
         if (this.m_slots[var2].character == var1) {
    return var2;
         }
      }

      return -1;
   }

    int getFreeSlot() {
      for (int var1 = 0; var1 < this.m_slots.length; var1++) {
         if (!this.m_slots[var1].playing) {
    return var1;
         }
      }

      return -1;
   }

    void stopNotPlaying() {
      for (int var1 = 0; var1 < this.m_slots.length; var1++) {
    Slot var2 = this.m_slots[var1];
         if (!var2.playing) {
            var2.stopPlaying();
            var2.character = nullptr;
         }
      }
   }

    void postUpdate() {
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

    void render() {
      if (Core.bDebug) {
      }
   }

    static void Reset() {
      for (int var0 = 0; var0 < instance.m_slots.length; var0++) {
         instance.m_slots[var0].stopPlaying();
         instance.m_slots[var0].character = nullptr;
         instance.m_slots[var0].playing = false;
      }
   }
}
} // namespace characters
} // namespace zombie
