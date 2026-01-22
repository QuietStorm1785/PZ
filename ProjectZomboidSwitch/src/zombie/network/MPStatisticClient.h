#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/iso/IsoUtils.h"
#include <algorithm>

namespace zombie {
namespace network {


class MPStatisticClient {
public:
    static MPStatisticClient instance = std::make_shared<MPStatisticClient>();
    bool needUpdate = true;
    int zombiesLocalOwnership = 0;
    float zombiesDesyncAVG = 0.0F;
    float zombiesDesyncMax = 0.0F;
    int zombiesTeleports = 0;
    float remotePlayersDesyncAVG = 0.0F;
    float remotePlayersDesyncMax = 0.0F;
    int remotePlayersTeleports = 0;
    float FPS = 0.0F;
    long lastRender = System.currentTimeMillis();
    short FPSAcc = 0;
   private float[] fpsArray = new float[1000];
    short fpsArrayCount = 0;

    static MPStatisticClient getInstance() {
    return instance;
   }

    void incrementZombiesTeleports() {
      this.zombiesTeleports++;
   }

    void incrementRemotePlayersTeleports() {
      this.remotePlayersTeleports++;
   }

    float getFPS() {
      return this.FPS;
   }

    void update() {
      if (this.needUpdate) {
         this.needUpdate = false;

         for (int var1 = 0; var1 < GameClient.IDToZombieMap.values().length; var1++) {
    IsoZombie var2 = (IsoZombie)GameClient.IDToZombieMap.values()[var1];
            if (!var2.isRemoteZombie()) {
               this.zombiesLocalOwnership++;
            } else {
    float var3 = IsoUtils.DistanceTo(var2.x, var2.y, var2.z, var2.realx, var2.realy, var2.realz);
               this.zombiesDesyncAVG = this.zombiesDesyncAVG + (var3 - this.zombiesDesyncAVG) * 0.05F;
               if (var3 > this.zombiesDesyncMax) {
                  this.zombiesDesyncMax = var3;
               }
            }
         }

         for (IsoPlayer var5 : GameClient.IDToPlayerMap.values()) {
            if (!var5.isLocalPlayer()) {
    float var6 = IsoUtils.DistanceTo(var5.x, var5.y, var5.z, var5.realx, var5.realy, var5.realz);
               this.remotePlayersDesyncAVG = this.remotePlayersDesyncAVG + (var6 - this.remotePlayersDesyncAVG) * 0.05F;
               if (var6 > this.remotePlayersDesyncMax) {
                  this.remotePlayersDesyncMax = var6;
               }
            }
         }
      }
   }

    void send(ByteBufferWriter var1) {
      var1.putInt(GameClient.IDToZombieMap.size());
      var1.putInt(this.zombiesLocalOwnership);
      var1.putFloat(this.zombiesDesyncAVG);
      var1.putFloat(this.zombiesDesyncMax);
      var1.putInt(this.zombiesTeleports);
      var1.putInt(GameClient.IDToPlayerMap.size());
      var1.putFloat(this.remotePlayersDesyncAVG);
      var1.putFloat(this.remotePlayersDesyncMax);
      var1.putInt(this.remotePlayersTeleports);
    void* var2 = nullptr;
    short var3 = 0;
      /* synchronized - TODO: add std::mutex */ (this.fpsArray) {
         var2 = (float[])this.fpsArray.clone();
         Arrays.fill(this.fpsArray, 0, this.fpsArrayCount, 0.0F);
         var3 = this.fpsArrayCount;
         this.fpsArrayCount = 0;
      }

    float var16 = (float)((Object[])var2)[0];
    float var5 = (float)((Object[])var2)[0];
    float var6 = (float)((Object[])var2)[0];
      short[] var7 = new short[32];
      Arrays.fill(var7, (short)0);

      for (int var8 = 1; var8 < var3; var8++) {
    float var9 = (float)((Object[])var2)[var8];
         if (var16 > var9) {
            var16 = var9;
         }

         if (var6 < var9) {
            var6 = var9;
         }

         var5 += var9;
      }

      var5 /= var3;
      if (var5 < var16 + 16.0F) {
         var16 = var5 - 16.0F;
      }

      if (var6 < var5 + 16.0F) {
         var6 = var5 + 16.0F;
      }

    float var18 = (var5 - var16) / (var7.length / 2);
    float var19 = (var6 - var5) / (var7.length / 2);

      for (int var10 = 0; var10 < var3; var10++) {
    float var11 = (float)((Object[])var2)[var10];
         if (var11 < var5) {
    int var12 = (int)Math.ceil((var11 - var16) / var18);
            var7[var12]++;
         }

         if (var11 >= var5) {
    int var21 = (int)Math.ceil((var11 - var5) / var19) + var7.length / 2 - 1;
            var7[var21]++;
         }
      }

      var1.putFloat(this.FPS);
      var1.putFloat(var16);
      var1.putFloat(var5);
      var1.putFloat(var6);

      for (int var20 = 0; var20 < var7.length; var20++) {
         var1.putShort(var7[var20]);
      }

      this.zombiesDesyncMax = 0.0F;
      this.zombiesTeleports = 0;
      this.remotePlayersDesyncMax = 0.0F;
      this.remotePlayersTeleports = 0;
      this.zombiesLocalOwnership = 0;
      this.needUpdate = true;
   }

    void fpsProcess() {
      this.FPSAcc++;
    long var1 = System.currentTimeMillis();
      if (var1 - this.lastRender >= 1000L) {
         this.FPS = this.FPSAcc;
         this.FPSAcc = 0;
         this.lastRender = var1;
         if (this.fpsArrayCount < this.fpsArray.length) {
            /* synchronized - TODO: add std::mutex */ (this.fpsArray) {
               this.fpsArray[this.fpsArrayCount] = this.FPS;
               this.fpsArrayCount++;
            }
         }
      }
   }
}
} // namespace network
} // namespace zombie
