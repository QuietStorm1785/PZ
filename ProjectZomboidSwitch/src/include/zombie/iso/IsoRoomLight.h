#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/opengl/RenderSettings.h"
#include "zombie/iso/LosUtil/TestResults.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/areas/IsoRoom.h"

namespace zombie {
namespace iso {


class IsoRoomLight {
public:
    static int NextID = 1;
    static int SHINE_DIST = 5;
    int ID;
    IsoRoom room;
    int x;
    int y;
    int z;
    int width;
    int height;
    float r;
    float g;
    float b;
    bool bActive;
    bool bActiveJNI;
    bool bHydroPowered = true;

    public IsoRoomLight(IsoRoom var1, int var2, int var3, int var4, int var5, int var6) {
      this.room = var1;
      this.x = var2;
      this.y = var3;
      this.z = var4;
      this.width = var5;
      this.height = var6;
      this.r = 0.9F;
      this.b = 0.8F;
      this.b = 0.7F;
      this.bActive = var1.def.bLightsActive;
   }

    void addInfluence() {
      this.r = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.8F * IsoGridSquare.rmod * 0.7F;
      this.g = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.8F * IsoGridSquare.gmod * 0.7F;
      this.b = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.8F * IsoGridSquare.bmod * 0.7F;
      this.r *= 2.0F;
      this.g *= 2.0F;
      this.b *= 2.0F;
      this.shineIn(this.x - 1, this.y, this.x, this.y + this.height, SHINE_DIST, 0);
      this.shineIn(this.x, this.y - 1, this.x + this.width, this.y, 0, SHINE_DIST);
      this.shineIn(this.x + this.width, this.y, this.x + this.width + 1, this.y + this.height, -SHINE_DIST, 0);
      this.shineIn(this.x, this.y + this.height, this.x + this.width, this.y + this.height + 1, 0, -SHINE_DIST);
    IsoGridSquare var1 = IsoWorld.instance.CurrentCell.getGridSquare(this.x, this.y, this.z);
      this.bActive = this.room.def.bLightsActive;
      if (!this.bHydroPowered || IsoWorld.instance.isHydroPowerOn() || var1 != nullptr && var1.haveElectricity()) {
         if (this.bActive) {
            this.r = 0.9F;
            this.g = 0.8F;
            this.b = 0.7F;

            for (int var2 = this.y; var2 < this.y + this.height; var2++) {
               for (int var3 = this.x; var3 < this.x + this.width; var3++) {
                  var1 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var2, this.z);
                  if (var1 != nullptr) {
                     var1.setLampostTotalR(var1.getLampostTotalR() + this.r);
                     var1.setLampostTotalG(var1.getLampostTotalG() + this.g);
                     var1.setLampostTotalB(var1.getLampostTotalB() + this.b);
                  }
               }
            }

            this.shineOut(this.x, this.y, this.x + 1, this.y + this.height, -SHINE_DIST, 0);
            this.shineOut(this.x, this.y, this.x + this.width, this.y + 1, 0, -SHINE_DIST);
            this.shineOut(this.x + this.width - 1, this.y, this.x + this.width, this.y + this.height, SHINE_DIST, 0);
            this.shineOut(this.x, this.y + this.height - 1, this.x + this.width, this.y + this.height, 0, SHINE_DIST);
         }
      } else {
         this.bActive = false;
      }
   }

    void shineOut(int var1, int var2, int var3, int var4, int var5, int var6) {
      for (int var7 = var2; var7 < var4; var7++) {
         for (int var8 = var1; var8 < var3; var8++) {
            this.shineOut(var8, var7, var5, var6);
         }
      }
   }

    void shineOut(int var1, int var2, int var3, int var4) {
      if (var3 > 0) {
         for (int var5 = 1; var5 <= var3; var5++) {
            this.shineFromTo(var1, var2, var1 + var5, var2);
         }
      } else if (var3 < 0) {
         for (int var6 = 1; var6 <= -var3; var6++) {
            this.shineFromTo(var1, var2, var1 - var6, var2);
         }
      } else if (var4 > 0) {
         for (int var7 = 1; var7 <= var4; var7++) {
            this.shineFromTo(var1, var2, var1, var2 + var7);
         }
      } else if (var4 < 0) {
         for (int var8 = 1; var8 <= -var4; var8++) {
            this.shineFromTo(var1, var2, var1, var2 - var8);
         }
      }
   }

    void shineFromTo(int var1, int var2, int var3, int var4) {
    IsoGridSquare var5 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, this.z);
      if (var5 != nullptr) {
         if (var5.getRoom() != this.room) {
    TestResults var6 = LosUtil.lineClear(IsoWorld.instance.CurrentCell, var1, var2, this.z, var3, var4, this.z, false);
            if (var6 != TestResults.Blocked) {
    float var7 = Math.abs(var1 - var3) + Math.abs(var2 - var4);
    float var8 = var7 / SHINE_DIST;
               var8 = 1.0F - var8;
               var8 *= var8;
    float var9 = var8 * this.r * 2.0F;
    float var10 = var8 * this.g * 2.0F;
    float var11 = var8 * this.b * 2.0F;
               var5.setLampostTotalR(var5.getLampostTotalR() + var9);
               var5.setLampostTotalG(var5.getLampostTotalG() + var10);
               var5.setLampostTotalB(var5.getLampostTotalB() + var11);
            }
         }
      }
   }

    void shineIn(int var1, int var2, int var3, int var4, int var5, int var6) {
      for (int var7 = var2; var7 < var4; var7++) {
         for (int var8 = var1; var8 < var3; var8++) {
            this.shineIn(var8, var7, var5, var6);
         }
      }
   }

    void shineIn(int var1, int var2, int var3, int var4) {
    IsoGridSquare var5 = IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, this.z);
      if (var5 != nullptr && var5.Is(IsoFlagType.exterior)) {
         if (var3 > 0) {
            for (int var6 = 1; var6 <= var3; var6++) {
               this.shineFromToIn(var1, var2, var1 + var6, var2);
            }
         } else if (var3 < 0) {
            for (int var7 = 1; var7 <= -var3; var7++) {
               this.shineFromToIn(var1, var2, var1 - var7, var2);
            }
         } else if (var4 > 0) {
            for (int var8 = 1; var8 <= var4; var8++) {
               this.shineFromToIn(var1, var2, var1, var2 + var8);
            }
         } else if (var4 < 0) {
            for (int var9 = 1; var9 <= -var4; var9++) {
               this.shineFromToIn(var1, var2, var1, var2 - var9);
            }
         }
      }
   }

    void shineFromToIn(int var1, int var2, int var3, int var4) {
    IsoGridSquare var5 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, this.z);
      if (var5 != nullptr) {
    TestResults var6 = LosUtil.lineClear(IsoWorld.instance.CurrentCell, var1, var2, this.z, var3, var4, this.z, false);
         if (var6 != TestResults.Blocked) {
    float var7 = Math.abs(var1 - var3) + Math.abs(var2 - var4);
    float var8 = var7 / SHINE_DIST;
            var8 = 1.0F - var8;
            var8 *= var8;
    float var9 = var8 * this.r * 2.0F;
    float var10 = var8 * this.g * 2.0F;
    float var11 = var8 * this.b * 2.0F;
            var5.setLampostTotalR(var5.getLampostTotalR() + var9);
            var5.setLampostTotalG(var5.getLampostTotalG() + var10);
            var5.setLampostTotalB(var5.getLampostTotalB() + var11);
         }
      }
   }

    void clearInfluence() {
      for (int var1 = this.y - SHINE_DIST; var1 < this.y + this.height + SHINE_DIST; var1++) {
         for (int var2 = this.x - SHINE_DIST; var2 < this.x + this.width + SHINE_DIST; var2++) {
    IsoGridSquare var3 = IsoWorld.instance.CurrentCell.getGridSquare(var2, var1, this.z);
            if (var3 != nullptr) {
               var3.setLampostTotalR(0.0F);
               var3.setLampostTotalG(0.0F);
               var3.setLampostTotalB(0.0F);
            }
         }
      }
   }

    bool isInBounds() {
      IsoChunkMap[] var1 = IsoWorld.instance.CurrentCell.ChunkMap;

      for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
         if (!var1[var2].ignore) {
    int var3 = var1[var2].getWorldXMinTiles();
    int var4 = var1[var2].getWorldXMaxTiles();
    int var5 = var1[var2].getWorldYMinTiles();
    int var6 = var1[var2].getWorldYMaxTiles();
            if (this.x - SHINE_DIST < var4 && this.x + this.width + SHINE_DIST > var3 && this.y - SHINE_DIST < var6 && this.y + this.height + SHINE_DIST > var5
               )
             {
    return true;
            }
         }
      }

    return false;
   }
}
} // namespace iso
} // namespace zombie
