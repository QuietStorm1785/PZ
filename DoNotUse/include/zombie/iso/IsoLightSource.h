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
#include "zombie/iso/areas/IsoBuilding.h"
#include "zombie/iso/objects/IsoLightSwitch.h"

namespace zombie {
namespace iso {


class IsoLightSource {
public:
    static int NextID = 1;
    int ID;
    int x;
    int y;
    int z;
    float r;
    float g;
    float b;
    float rJNI;
    float gJNI;
    float bJNI;
    int radius;
    bool bActive;
    bool bWasActive;
    bool bActiveJNI;
    int life = -1;
    int startlife = -1;
    IsoBuilding localToBuilding;
    bool bHydroPowered = false;
   public std::vector<IsoLightSwitch> switches = new std::vector<>(0);
    IsoChunk chunk;
    void* lightMap;

    public IsoLightSource(int var1, int var2, int var3, float var4, float var5, float var6, int var7) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
      this.r = var4;
      this.g = var5;
      this.b = var6;
      this.radius = var7;
      this.bActive = true;
   }

    public IsoLightSource(int var1, int var2, int var3, float var4, float var5, float var6, int var7, IsoBuilding var8) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
      this.r = var4;
      this.g = var5;
      this.b = var6;
      this.radius = var7;
      this.bActive = true;
      this.localToBuilding = var8;
   }

    public IsoLightSource(int var1, int var2, int var3, float var4, float var5, float var6, int var7, int var8) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
      this.r = var4;
      this.g = var5;
      this.b = var6;
      this.radius = var7;
      this.bActive = true;
      this.startlife = this.life = var8;
   }

    void update() {
    IsoGridSquare var1 = IsoWorld.instance.CurrentCell.getGridSquare(this.x, this.y, this.z);
      if (!this.bHydroPowered || IsoWorld.instance.isHydroPowerOn() || var1 != nullptr && var1.haveElectricity()) {
         if (this.bActive) {
            if (this.localToBuilding != nullptr) {
               this.r = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.7F;
               this.g = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.7F;
               this.b = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.7F;
            }

            if (this.life > 0) {
               this.life--;
            }

            if (this.localToBuilding != nullptr && var1 != nullptr) {
               this.r = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.8F * IsoGridSquare.rmod * 0.7F;
               this.g = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.8F * IsoGridSquare.gmod * 0.7F;
               this.b = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.8F * IsoGridSquare.bmod * 0.7F;
            }

            for (int var2 = this.x - this.radius; var2 < this.x + this.radius; var2++) {
               for (int var3 = this.y - this.radius; var3 < this.y + this.radius; var3++) {
                  for (int var4 = 0; var4 < 8; var4++) {
                     var1 = IsoWorld.instance.CurrentCell.getGridSquare(var2, var3, var4);
                     if (var1 != nullptr && (this.localToBuilding == nullptr || this.localToBuilding == var1.getBuilding())) {
    TestResults var5 = LosUtil.lineClear(var1.getCell(), this.x, this.y, this.z, var1.getX(), var1.getY(), var1.getZ(), false);
                        if (var1.getX() == this.x && var1.getY() == this.y && var1.getZ() == this.z || var5 != TestResults.Blocked) {
    float var6 = 0.0F;
    float var7;
                           if (Math.abs(var1.getZ() - this.z) <= 1) {
                              var7 = IsoUtils.DistanceTo(this.x, this.y, 0.0F, var1.getX(), var1.getY(), 0.0F);
                           } else {
                              var7 = IsoUtils.DistanceTo(this.x, this.y, this.z, var1.getX(), var1.getY(), var1.getZ());
                           }

                           if (!(var7 > this.radius)) {
                              var6 = var7 / this.radius;
                              var6 = 1.0F - var6;
                              var6 *= var6;
                              if (this.life > -1) {
                                 var6 *= (float)this.life / this.startlife;
                              }

    float var8 = var6 * this.r * 2.0F;
    float var9 = var6 * this.g * 2.0F;
    float var10 = var6 * this.b * 2.0F;
                              var1.setLampostTotalR(var1.getLampostTotalR() + var8);
                              var1.setLampostTotalG(var1.getLampostTotalG() + var9);
                              var1.setLampostTotalB(var1.getLampostTotalB() + var10);
                           }
                        }
                     }
                  }
               }
            }
         }
      } else {
         this.bActive = false;
      }
   }

    int getX() {
      return this.x;
   }

    void setX(int var1) {
      this.x = var1;
   }

    int getY() {
      return this.y;
   }

    void setY(int var1) {
      this.y = var1;
   }

    int getZ() {
      return this.z;
   }

    void setZ(int var1) {
      this.z = var1;
   }

    float getR() {
      return this.r;
   }

    void setR(float var1) {
      this.r = var1;
   }

    float getG() {
      return this.g;
   }

    void setG(float var1) {
      this.g = var1;
   }

    float getB() {
      return this.b;
   }

    void setB(float var1) {
      this.b = var1;
   }

    int getRadius() {
      return this.radius;
   }

    void setRadius(int var1) {
      this.radius = var1;
   }

    bool isActive() {
      return this.bActive;
   }

    void setActive(bool var1) {
      this.bActive = var1;
   }

    bool wasActive() {
      return this.bWasActive;
   }

    void setWasActive(bool var1) {
      this.bWasActive = var1;
   }

   public std::vector<IsoLightSwitch> getSwitches() {
      return this.switches;
   }

    void setSwitches(std::vector<IsoLightSwitch> var1) {
      this.switches = var1;
   }

    void clearInfluence() {
      for (int var1 = this.x - this.radius; var1 < this.x + this.radius; var1++) {
         for (int var2 = this.y - this.radius; var2 < this.y + this.radius; var2++) {
            for (int var3 = 0; var3 < 8; var3++) {
    IsoGridSquare var4 = IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, var3);
               if (var4 != nullptr) {
                  var4.setLampostTotalR(0.0F);
                  var4.setLampostTotalG(0.0F);
                  var4.setLampostTotalB(0.0F);
               }
            }
         }
      }
   }

    bool isInBounds(int var1, int var2, int var3, int var4) {
      return this.x >= var1 && this.x < var3 && this.y >= var2 && this.y < var4;
   }

    bool isInBounds() {
      IsoChunkMap[] var1 = IsoWorld.instance.CurrentCell.ChunkMap;

      for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
         if (!var1[var2].ignore) {
    int var3 = var1[var2].getWorldXMinTiles();
    int var4 = var1[var2].getWorldXMaxTiles();
    int var5 = var1[var2].getWorldYMinTiles();
    int var6 = var1[var2].getWorldYMaxTiles();
            if (this.isInBounds(var3, var5, var4, var6)) {
    return true;
            }
         }
      }

    return false;
   }

    bool isHydroPowered() {
      return this.bHydroPowered;
   }

    IsoBuilding getLocalToBuilding() {
      return this.localToBuilding;
   }
}
} // namespace iso
} // namespace zombie
