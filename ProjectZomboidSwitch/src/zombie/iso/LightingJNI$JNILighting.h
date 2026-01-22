#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/iso/IsoGridSquare/ILighting.h"
#include "zombie/iso/IsoGridSquare/ResultLight.h"
#include "zombie/meta/Meta.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace iso {


class LightingJNI {
public:
    static const int RESULT_LIGHTS_PER_SQUARE = 5;
   private static const int[] lightInts = new int[43];
    static const uint8_t VIS_SEEN = 1;
    static const uint8_t VIS_CAN_SEE = 2;
    static const uint8_t VIS_COULD_SEE = 4;
    int playerIndex;
    const IsoGridSquare square;
    ColorInfo lightInfo = std::make_shared<ColorInfo>();
    uint8_t vis;
    float cacheDarkMulti;
    float cacheTargetDarkMulti;
   private int[] cacheVertLight;
    int updateTick = -1;
    int lightsCount;
   private ResultLight[] lights;

   public LightingJNI$JNILighting(int var1, IsoGridSquare var2) {
      this.playerIndex = var1;
      this.square = var2;
      this.cacheDarkMulti = 0.0F;
      this.cacheTargetDarkMulti = 0.0F;
      this.cacheVertLight = new int[8];

      for (int var3 = 0; var3 < 8; var3++) {
         this.cacheVertLight[var3] = 0;
      }
   }

    int lightverts(int var1) {
      return this.cacheVertLight[var1];
   }

    float lampostTotalR() {
      return 0.0F;
   }

    float lampostTotalG() {
      return 0.0F;
   }

    float lampostTotalB() {
      return 0.0F;
   }

    bool bSeen() {
      this.update();
      return (this.vis & 1) != 0;
   }

    bool bCanSee() {
      this.update();
      return (this.vis & 2) != 0;
   }

    bool bCouldSee() {
      this.update();
      return (this.vis & 4) != 0;
   }

    float darkMulti() {
      return this.cacheDarkMulti;
   }

    float targetDarkMulti() {
      return this.cacheTargetDarkMulti;
   }

    ColorInfo lightInfo() {
      this.update();
      return this.lightInfo;
   }

    void lightverts(int var1, int var2) {
      throw std::make_unique<IllegalStateException>();
   }

    void lampostTotalR(float var1) {
      throw std::make_unique<IllegalStateException>();
   }

    void lampostTotalG(float var1) {
      throw std::make_unique<IllegalStateException>();
   }

    void lampostTotalB(float var1) {
      throw std::make_unique<IllegalStateException>();
   }

    void bSeen(bool var1) {
      throw std::make_unique<IllegalStateException>();
   }

    void bCanSee(bool var1) {
      throw std::make_unique<IllegalStateException>();
   }

    void bCouldSee(bool var1) {
      throw std::make_unique<IllegalStateException>();
   }

    void darkMulti(float var1) {
      throw std::make_unique<IllegalStateException>();
   }

    void targetDarkMulti(float var1) {
      throw std::make_unique<IllegalStateException>();
   }

    int resultLightCount() {
      return this.lightsCount;
   }

    ResultLight getResultLight(int var1) {
      return this.lights[var1];
   }

    void reset() {
      this.updateTick = -1;
   }

    void update() {
      if (LightingJNI.updateCounter[this.playerIndex] != -1) {
         if (this.updateTick != LightingJNI.updateCounter[this.playerIndex]
            && LightingJNI.getSquareLighting(this.playerIndex, this.square.x, this.square.y, this.square.z, lightInts)) {
    IsoPlayer var1 = IsoPlayer.players[this.playerIndex];
    bool var2 = (this.vis & 1) != 0;
    int var3 = 0;
            this.vis = (byte)(lightInts[var3++] & 7);
            this.lightInfo.r = (lightInts[var3] & 0xFF) / 255.0F;
            this.lightInfo.g = (lightInts[var3] >> 8 & 0xFF) / 255.0F;
            this.lightInfo.b = (lightInts[var3++] >> 16 & 0xFF) / 255.0F;
            this.cacheDarkMulti = lightInts[var3++] / 100000.0F;
            this.cacheTargetDarkMulti = lightInts[var3++] / 100000.0F;
    float var4 = 1.0F;
    float var5 = 1.0F;
            if (var1 != nullptr) {
    int var6 = this.square.z - (int)var1.z;
               if (var6 == -1) {
                  var4 = 1.0F;
                  var5 = 0.85F;
               } else if (var6 < -1) {
                  var4 = 0.85F;
                  var5 = 0.85F;
               }

               if ((this.vis & 2) == 0 && (this.vis & 4) != 0) {
    int var7 = (int)var1.x;
    int var8 = (int)var1.y;
    int var9 = this.square.x - var7;
    int var10 = this.square.y - var8;
                  if (var1.dir != IsoDirections.Max && Math.abs(var9) <= 2 && Math.abs(var10) <= 2) {
                     int[] var11 = LightingJNI.ForcedVis[var1.dir.index()];

                     for (byte var12 = 0; var12 < var11.length; var12 += 2) {
                        if (var9 == var11[var12] && var10 == var11[var12 + 1]) {
                           this.vis = (byte)(this.vis | 2);
                           break;
                        }
                     }
                  }
               }
            }

            for (int var23 = 0; var23 < 4; var23++) {
    int var27 = lightInts[var3++];
    float var30 = (var27 & 0xFF) * var5;
    float var32 = ((var27 & 0xFF00) >> 8) * var5;
    float var34 = ((var27 & 0xFF0000) >> 16) * var5;
               this.cacheVertLight[var23] = (int)var30 << 0 | (int)var32 << 8 | (int)var34 << 16 | 0xFF000000;
            }

            for (int var24 = 4; var24 < 8; var24++) {
    int var28 = lightInts[var3++];
    float var31 = (var28 & 0xFF) * var4;
    float var33 = ((var28 & 0xFF00) >> 8) * var4;
    float var35 = ((var28 & 0xFF0000) >> 16) * var4;
               this.cacheVertLight[var24] = (int)var31 << 0 | (int)var33 << 8 | (int)var35 << 16 | 0xFF000000;
            }

            this.lightsCount = lightInts[var3++];

            for (int var25 = 0; var25 < this.lightsCount; var25++) {
               if (this.lights == nullptr) {
                  this.lights = new ResultLight[5];
               }

               if (this.lights[var25] == nullptr) {
                  this.lights[var25] = std::make_unique<ResultLight>();
               }

               this.lights[var25].id = lightInts[var3++];
               this.lights[var25].x = lightInts[var3++];
               this.lights[var25].y = lightInts[var3++];
               this.lights[var25].z = lightInts[var3++];
               this.lights[var25].radius = lightInts[var3++];
    int var29 = lightInts[var3++];
               this.lights[var25].r = (var29 & 0xFF) / 255.0F;
               this.lights[var25].g = (var29 >> 8 & 0xFF) / 255.0F;
               this.lights[var25].b = (var29 >> 16 & 0xFF) / 255.0F;
               this.lights[var25].flags = var29 >> 24 & 0xFF;
            }

            this.updateTick = LightingJNI.updateCounter[this.playerIndex];
            if ((this.vis & 1) != 0) {
               if (var2 && this.square.getRoom() != nullptr && this.square.getRoom().def != nullptr && !this.square.getRoom().def.bExplored) {
    bool var26 = true;
               }

               this.square.checkRoomSeen(this.playerIndex);
               if (!var2) {
                  if (!$assertionsDisabled && GameServer.bServer) {
                     throw std::make_unique<AssertionError>();
                  }

                  if (!GameClient.bClient) {
                     Meta.instance.dealWithSquareSeen(this.square);
                  }
               }
            }
         }
      }
   }
}
} // namespace iso
} // namespace zombie
