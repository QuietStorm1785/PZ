#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/SandboxOptions.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/RoomDef/RoomRect.h"
#include <algorithm>

namespace zombie {
namespace iso {


class IsoMetaChunk {
public:
    static const float zombiesMinPerChunk = 0.06F;
    static const float zombiesFullPerChunk = 12.0F;
    int ZombieIntensity = 0;
   private Zone[] zones;
    int zonesSize;
   private RoomDef[] rooms;
    int roomsSize;

    float getZombieIntensity(bool var1) {
    float var2 = this.ZombieIntensity;
    float var3 = var2 / 255.0F;
      if (SandboxOptions.instance.Distribution.getValue() == 2) {
         var2 = 128.0F;
         var3 = 0.5F;
      }

      var2 *= 0.5F;
      if (SandboxOptions.instance.Zombies.getValue() == 1) {
         var2 *= 4.0F;
      } else if (SandboxOptions.instance.Zombies.getValue() == 2) {
         var2 *= 3.0F;
      } else if (SandboxOptions.instance.Zombies.getValue() == 3) {
         var2 *= 2.0F;
      } else if (SandboxOptions.instance.Zombies.getValue() == 5) {
         var2 *= 0.35F;
      } else if (SandboxOptions.instance.Zombies.getValue() == 6) {
         var2 = 0.0F;
      }

      var3 = var2 / 255.0F;
    float var4 = 11.94F;
      var4 *= var3;
      var2 = 0.06F + var4;
      if (!var1) {
    return var2;
      } else {
    float var5 = var3 * 10.0F;
         if (Rand.Next(3) == 0) {
            return 0.0F;
         } else {
            var5 *= 0.5F;
    int var6 = 1000;
            if (SandboxOptions.instance.Zombies.getValue() == 1) {
               var6 = (int)(var6 / 2.0F);
            } else if (SandboxOptions.instance.Zombies.getValue() == 2) {
               var6 = (int)(var6 / 1.7F);
            } else if (SandboxOptions.instance.Zombies.getValue() == 3) {
               var6 = (int)(var6 / 1.5F);
            } else if (SandboxOptions.instance.Zombies.getValue() == 5) {
               var6 = (int)(var6 * 1.5F);
            }

            if (Rand.Next(var6) < var5 && IsoWorld.getZombiesEnabled()) {
               var2 = 120.0F;
               if (var2 > 12.0F) {
                  var2 = 12.0F;
               }
            }

    return var2;
         }
      }
   }

    float getZombieIntensity() {
      return this.getZombieIntensity(true);
   }

    void setZombieIntensity(int var1) {
      if (var1 >= 0) {
         this.ZombieIntensity = var1;
      }
   }

    float getLootZombieIntensity() {
    float var1 = this.ZombieIntensity;
    float var2 = var1 / 255.0F;
      var2 = var1 / 255.0F;
    float var3 = 11.94F;
      var3 *= var2;
      var1 = 0.06F + var3;
    float var4 = var2 * 10.0F;
      var2 = var2 * var2 * var2;
      if (Rand.Next(300) <= var4) {
         var1 = 120.0F;
      }

      return IsoWorld.getZombiesDisabled() ? 400.0F : var1;
   }

    int getUnadjustedZombieIntensity() {
      return this.ZombieIntensity;
   }

    void addZone(Zone var1) {
      if (this.zones == nullptr) {
         this.zones = new Zone[8];
      }

      if (this.zonesSize == this.zones.length) {
         Zone[] var2 = new Zone[this.zones.length + 8];
         System.arraycopy(this.zones, 0, var2, 0, this.zonesSize);
         this.zones = var2;
      }

      this.zones[this.zonesSize++] = var1;
   }

    void removeZone(Zone var1) {
      if (this.zones != nullptr) {
         for (int var2 = 0; var2 < this.zonesSize; var2++) {
            if (this.zones[var2] == var1) {
               while (var2 < this.zonesSize - 1) {
                  this.zones[var2] = this.zones[var2 + 1];
                  var2++;
               }

               this.zones[this.zonesSize - 1] = nullptr;
               this.zonesSize--;
               break;
            }
         }
      }
   }

    Zone getZone(int var1) {
      return var1 >= 0 && var1 < this.zonesSize ? this.zones[var1] : nullptr;
   }

    Zone getZoneAt(int var1, int var2, int var3) {
      if (this.zones != nullptr && this.zonesSize > 0) {
    Zone var4 = nullptr;

         for (int var5 = this.zonesSize - 1; var5 >= 0; var5--) {
    Zone var6 = this.zones[var5];
            if (var6.contains(var1, var2, var3)) {
               if (var6.isPreferredZoneForSquare) {
    return var6;
               }

               if (var4 == nullptr) {
                  var4 = var6;
               }
            }
         }

    return var4;
      } else {
    return nullptr;
      }
   }

   public std::vector<Zone> getZonesAt(int var1, int var2, int var3, std::vector<Zone> var4) {
      for (int var5 = 0; var5 < this.zonesSize; var5++) {
    Zone var6 = this.zones[var5];
         if (var6.contains(var1, var2, var3)) {
            var4.push_back(var6);
         }
      }

    return var4;
   }

    void getZonesUnique(Set<Zone> var1) {
      for (int var2 = 0; var2 < this.zonesSize; var2++) {
    Zone var3 = this.zones[var2];
         var1.push_back(var3);
      }
   }

    void getZonesIntersecting(int var1, int var2, int var3, int var4, int var5, std::vector<Zone> var6) {
      for (int var7 = 0; var7 < this.zonesSize; var7++) {
    Zone var8 = this.zones[var7];
         if (!var6.contains(var8) && var8.intersects(var1, var2, var3, var4, var5)) {
            var6.push_back(var8);
         }
      }
   }

    void clearZones() {
      if (this.zones != nullptr) {
         for (int var1 = 0; var1 < this.zones.length; var1++) {
            this.zones[var1] = nullptr;
         }
      }

      this.zones = nullptr;
      this.zonesSize = 0;
   }

    void clearRooms() {
      if (this.rooms != nullptr) {
         for (int var1 = 0; var1 < this.rooms.length; var1++) {
            this.rooms[var1] = nullptr;
         }
      }

      this.rooms = nullptr;
      this.roomsSize = 0;
   }

    int numZones() {
      return this.zonesSize;
   }

    void addRoom(RoomDef var1) {
      if (this.rooms == nullptr) {
         this.rooms = new RoomDef[8];
      }

      if (this.roomsSize == this.rooms.length) {
         RoomDef[] var2 = new RoomDef[this.rooms.length + 8];
         System.arraycopy(this.rooms, 0, var2, 0, this.roomsSize);
         this.rooms = var2;
      }

      this.rooms[this.roomsSize++] = var1;
   }

    RoomDef getRoomAt(int var1, int var2, int var3) {
      for (int var4 = 0; var4 < this.roomsSize; var4++) {
    RoomDef var5 = this.rooms[var4];
         if (!var5.isEmptyOutside() && var5.level == var3) {
            for (int var6 = 0; var6 < var5.rects.size(); var6++) {
    RoomRect var7 = (RoomRect)var5.rects.get(var6);
               if (var7.x <= var1 && var7.y <= var2 && var1 < var7.getX2() && var2 < var7.getY2()) {
    return var5;
               }
            }
         }
      }

    return nullptr;
   }

    RoomDef getEmptyOutsideAt(int var1, int var2, int var3) {
      for (int var4 = 0; var4 < this.roomsSize; var4++) {
    RoomDef var5 = this.rooms[var4];
         if (var5.isEmptyOutside() && var5.level == var3) {
            for (int var6 = 0; var6 < var5.rects.size(); var6++) {
    RoomRect var7 = (RoomRect)var5.rects.get(var6);
               if (var7.x <= var1 && var7.y <= var2 && var1 < var7.getX2() && var2 < var7.getY2()) {
    return var5;
               }
            }
         }
      }

    return nullptr;
   }

    int getNumRooms() {
      return this.roomsSize;
   }

    void getRoomsIntersecting(int var1, int var2, int var3, int var4, std::vector<RoomDef> var5) {
      for (int var6 = 0; var6 < this.roomsSize; var6++) {
    RoomDef var7 = this.rooms[var6];
         if (!var7.isEmptyOutside() && !var5.contains(var7) && var7.intersects(var1, var2, var3, var4)) {
            var5.push_back(var7);
         }
      }
   }

    void Dispose() {
      if (this.rooms != nullptr) {
         Arrays.fill(this.rooms, nullptr);
      }

      if (this.zones != nullptr) {
         Arrays.fill(this.zones, nullptr);
      }
   }
}
} // namespace iso
} // namespace zombie
