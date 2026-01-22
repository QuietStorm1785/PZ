#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/areas/isoregion/regions/IWorldRegion.h"
#include "zombie/iso/areas/isoregion/regions/IsoWorldRegion.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace iso {
namespace weather {
namespace fx {


class WeatherFxMask {
public:
   private WeatherFxMask[] masks;
    int maskPointer = 0;
    bool maskEnabled = false;
    IsoGridSquare plrSquare;
    int DISABLED_MASKS = 0;
    bool requiresUpdate = false;
    bool hasMaskToDraw = true;
    int playerIndex;
    IsoPlayer player;
    int playerZ;
    IWorldRegion curIsoWorldRegion;
   private std::vector<IWorldRegion> curConnectedRegions = std::make_unique<std::vector<>>();
   private const std::vector<IWorldRegion> isoWorldRegionTemp = std::make_unique<std::vector<>>();
    bool DIAMOND_ITER_DONE = false;
    bool isFirstSquare = true;
    IsoGridSquare firstSquare;

    void init() {
      this.masks = new WeatherFxMask[30000];

      for (int var1 = 0; var1 < this.masks.length; var1++) {
         if (this.masks[var1] == nullptr) {
            this.masks[var1] = std::make_unique<WeatherFxMask>();
         }
      }

      this.maskEnabled = true;
   }

    void initMask() {
      if (!GameServer.bServer) {
         if (!this.maskEnabled) {
            this.init();
         }

         this.playerIndex = IsoCamera.frameState.playerIndex;
         this.player = IsoPlayer.players[this.playerIndex];
         this.playerZ = (int)this.player.getZ();
         this.DIAMOND_ITER_DONE = false;
         this.requiresUpdate = false;
         if (this.player != nullptr) {
            if (this.isFirstSquare || this.plrSquare == nullptr || this.plrSquare != this.player.getSquare()) {
               this.plrSquare = this.player.getSquare();
               this.maskPointer = 0;
               this.DISABLED_MASKS = 0;
               this.requiresUpdate = true;
               if (this.firstSquare == nullptr) {
                  this.firstSquare = this.plrSquare;
               }

               if (this.firstSquare != nullptr && this.firstSquare != this.plrSquare) {
                  this.isFirstSquare = false;
               }
            }

            this.curIsoWorldRegion = this.player.getMasterRegion();
            this.curConnectedRegions.clear();
            if (this.curIsoWorldRegion != nullptr && this.player.getMasterRegion().isFogMask()) {
               this.isoWorldRegionTemp.clear();
               this.isoWorldRegionTemp.push_back(this.curIsoWorldRegion);

               while (this.isoWorldRegionTemp.size() > 0) {
    IWorldRegion var1 = this.isoWorldRegionTemp.remove(0);
                  this.curConnectedRegions.push_back(var1);
                  if (var1.getNeighbors().size() != 0) {
                     for (IsoWorldRegion var3 : var1.getNeighbors()) {
                        if (!this.isoWorldRegionTemp.contains(var3) && !this.curConnectedRegions.contains(var3) && var3.isFogMask()) {
                           this.isoWorldRegionTemp.push_back(var3);
                        }
                     }
                  }
               }
            } else {
               this.curIsoWorldRegion = nullptr;
            }
         }

         if (IsoWeatherFX.instance == nullptr) {
            this.hasMaskToDraw = false;
         } else {
            this.hasMaskToDraw = true;
            if (this.hasMaskToDraw) {
               if ((this.player.getSquare() == nullptr || this.player.getSquare().getBuilding() == nullptr && this.player.getSquare().Is(IsoFlagType.exterior))
                  && (this.curIsoWorldRegion == nullptr || !this.curIsoWorldRegion.isFogMask())) {
                  this.hasMaskToDraw = false;
               } else {
                  this.hasMaskToDraw = true;
               }
            }
         }
      }
   }

    void addMask(int var1, int var2, int var3, IsoGridSquare var4, int var5) {
      this.addMask(var1, var2, var3, var4, var5, true);
   }

    void addMask(int var1, int var2, int var3, IsoGridSquare var4, int var5, bool var6) {
      if (this.hasMaskToDraw && this.requiresUpdate) {
         if (!this.maskEnabled) {
            this.init();
         }

    WeatherFxMask var7 = this.getMask(var1, var2, var3);
         if (var7 == nullptr) {
    WeatherFxMask var8 = this.getFreeMask();
            var8.x = var1;
            var8.y = var2;
            var8.z = var3;
            var8.flags = var5;
            var8.gs = var4;
            var8.enabled = var6;
            if (!var6 && this.DISABLED_MASKS < WeatherFxMask.DIAMOND_ROWS) {
               this.DISABLED_MASKS++;
            }
         } else {
            if (var7.flags != var5) {
               var7.flags |= var5;
            }

            if (!var7.enabled && var6) {
    WeatherFxMask var9 = this.getFreeMask();
               var9.x = var1;
               var9.y = var2;
               var9.z = var3;
               var9.flags = var7.flags;
               var9.gs = var4;
               var9.enabled = var6;
            } else {
               var7.enabled = var7.enabled ? var7.enabled : var6;
               if (var6 && var4 != nullptr && var7.gs == nullptr) {
                  var7.gs = var4;
               }
            }
         }
      }
   }

    WeatherFxMask getFreeMask() {
      if (this.maskPointer >= this.masks.length) {
         DebugLog.log("Weather Mask buffer out of bounds. Increasing cache.");
         WeatherFxMask[] var1 = this.masks;
         this.masks = new WeatherFxMask[this.masks.length + 10000];

         for (int var2 = 0; var2 < this.masks.length; var2++) {
            if (var1[var2] != nullptr) {
               this.masks[var2] = var1[var2];
            } else {
               this.masks[var2] = std::make_unique<WeatherFxMask>();
            }
         }
      }

      return this.masks[this.maskPointer++];
   }

    bool masksContains(int var1, int var2, int var3) {
      return this.getMask(var1, var2, var3) != nullptr;
   }

    WeatherFxMask getMask(int var1, int var2, int var3) {
      if (this.maskPointer <= 0) {
    return nullptr;
      } else {
    int var4 = this.maskPointer - 1 - (WeatherFxMask.DIAMOND_ROWS + this.DISABLED_MASKS);
         if (var4 < 0) {
            var4 = 0;
         }

         for (int var5 = this.maskPointer - 1; var5 >= var4; var5--) {
            if (this.masks[var5].isLoc(var1, var2, var3)) {
               return this.masks[var5];
            }
         }

    return nullptr;
      }
   }
}
} // namespace fx
} // namespace weather
} // namespace iso
} // namespace zombie
