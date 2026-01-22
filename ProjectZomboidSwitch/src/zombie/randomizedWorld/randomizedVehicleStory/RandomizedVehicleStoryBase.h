#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector2f.h"
#include "zombie/SandboxOptions.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"
#include "zombie/randomizedWorld/RandomizedWorldBase.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/VehicleStorySpawner/Element.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <iterator>

namespace zombie {
namespace randomizedWorld {
namespace randomizedVehicleStory {


class RandomizedVehicleStoryBase : public RandomizedWorldBase {
public:
    int chance = 0;
    static int totalChance = 0;
   private static std::unordered_map<RandomizedVehicleStoryBase, int> rvsMap = std::make_unique<std::unordered_map<>>();
    bool horizontalZone = false;
    int zoneWidth = 0;
    static const float baseChance = 12.5F;
    int minX = 0;
    int minY = 0;
    int maxX = 0;
    int maxY = 0;
    int minZoneWidth = 0;
    int minZoneHeight = 0;

    static void initAllRVSMapChance(Zone var0, IsoChunk var1) {
      totalChance = 0;
      rvsMap.clear();

      for (int var2 = 0; var2 < IsoWorld.instance.getRandomizedVehicleStoryList().size(); var2++) {
    RandomizedVehicleStoryBase var3 = (RandomizedVehicleStoryBase)IsoWorld.instance.getRandomizedVehicleStoryList().get(var2);
         if (var3.isValid(var0, var1, false) && var3.isTimeValid(false)) {
            totalChance = totalChance + var3.getChance();
            rvsMap.put(var3, var3.getChance());
         }
      }
   }

    static bool doRandomStory(Zone var0, IsoChunk var1, bool var2) {
    float var3 = Rand.Next(0.0F, 500.0F);
      switch (SandboxOptions.instance.VehicleStoryChance.getValue()) {
         case 1:
    return false;
         case 2:
            var3 = Rand.Next(0.0F, 1000.0F);
         case 3:
         default:
            break;
         case 4:
            var3 = Rand.Next(0.0F, 300.0F);
            break;
         case 5:
            var3 = Rand.Next(0.0F, 175.0F);
            break;
         case 6:
            var3 = Rand.Next(0.0F, 50.0F);
      }

      if (var3 < 12.5F) {
         if (!var1.vehicles.empty()) {
    return false;
         } else {
    RandomizedVehicleStoryBase var4 = nullptr;
            initAllRVSMapChance(var0, var1);
            var4 = getRandomStory();
            if (var4 == nullptr) {
    return false;
            } else {
    VehicleStorySpawnData var5 = var4.initSpawnDataForChunk(var0, var1);
               var1.setRandomVehicleStoryToSpawnLater(var5);
    return true;
            }
         }
      } else {
    return false;
      }
   }

    static RandomizedVehicleStoryBase getRandomStory() {
    int var0 = Rand.Next(totalChance);
    Iterator var1 = rvsMap.keySet().iterator();
    int var2 = 0;

      while (var1.hasNext()) {
    RandomizedVehicleStoryBase var3 = (RandomizedVehicleStoryBase)var1.next();
         var2 += rvsMap.get(var3);
         if (var0 < var2) {
    return var3;
         }
      }

    return nullptr;
   }

    int getMinZoneWidth() {
      return this.minZoneWidth <= 0 ? 10 : this.minZoneWidth;
   }

    int getMinZoneHeight() {
      return this.minZoneHeight <= 0 ? 5 : this.minZoneHeight;
   }

    void randomizeVehicleStory(Zone var1, IsoChunk var2) {
   }

    IsoGridSquare getCenterOfChunk(Zone var1, IsoChunk var2) {
    int var3 = Math.max(var1.x, var2.wx * 10);
    int var4 = Math.max(var1.y, var2.wy * 10);
    int var5 = Math.min(var1.x + var1.w, (var2.wx + 1) * 10);
    int var6 = Math.min(var1.y + var1.h, (var2.wy + 1) * 10);
    int var7 = 0;
    int var8 = 0;
      if (this.horizontalZone) {
         var8 = (var1.y + var1.y + var1.h) / 2;
         var7 = (var3 + var5) / 2;
      } else {
         var8 = (var4 + var6) / 2;
         var7 = (var1.x + var1.x + var1.w) / 2;
      }

      return IsoCell.getInstance().getGridSquare(var7, var8, var1.z);
   }

    bool isValid(Zone var1, IsoChunk var2, bool var3) {
      this.horizontalZone = false;
      this.zoneWidth = 0;
      this.debugLine = "";
      if (!var3 && var1.hourLastSeen != 0) {
    return false;
      } else if (!var3 && var1.haveConstruction) {
    return false;
      } else if (!"Nav" == var1.getType())) {
         this.debugLine = this.debugLine + "Not a 'Nav' zone.";
    return false;
      } else {
         this.minX = Math.max(var1.x, var2.wx * 10);
         this.minY = Math.max(var1.y, var2.wy * 10);
         this.maxX = Math.min(var1.x + var1.w, (var2.wx + 1) * 10);
         this.maxY = Math.min(var1.y + var1.h, (var2.wy + 1) * 10);
         return this.getSpawnPoint(var1, var2, nullptr);
      }
   }

    VehicleStorySpawnData initSpawnDataForChunk(Zone var1, IsoChunk var2) {
    int var3 = this.getMinZoneWidth();
    int var4 = this.getMinZoneHeight();
      float[] var5 = new float[3];
      if (!this.getSpawnPoint(var1, var2, var5)) {
    return nullptr;
      } else {
    float var6 = var5[0];
    float var7 = var5[1];
    float var8 = var5[2];
         int[] var9 = new int[4];
         VehicleStorySpawner.getInstance().getAABB(var6, var7, var3, var4, var8, var9);
         return std::make_shared<VehicleStorySpawnData>(this, var1, var6, var7, var8, var9[0], var9[1], var9[2], var9[3]);
      }
   }

    bool getSpawnPoint(Zone var1, IsoChunk var2, float[] var3) {
      return this.getRectangleSpawnPoint(var1, var2, var3) || this.getPolylineSpawnPoint(var1, var2, var3);
   }

    bool getRectangleSpawnPoint(Zone var1, IsoChunk var2, float[] var3) {
      if (!var1.isRectangle()) {
    return false;
      } else {
    int var4 = this.getMinZoneWidth();
    int var5 = this.getMinZoneHeight();
         if (var1.w > 30 && var1.h < 15) {
            this.horizontalZone = true;
            this.zoneWidth = var1.h;
            if (var1.getWidth() < var5) {
               this.debugLine = "Horizontal street is too small, w:" + var1.getWidth() + " h:" + var1.getHeight();
    return false;
            } else if (var1.getHeight() < var4) {
               this.debugLine = "Horizontal street is too small, w:" + var1.getWidth() + " h:" + var1.getHeight();
    return false;
            } else if (var3 == nullptr) {
    return true;
            } else {
    float var9 = var1.getX();
    float var10 = var1.getX() + var1.getWidth();
    float var11 = var1.getY() + var1.getHeight() / 2.0F;
               var3[0] = PZMath.clamp(var2.wx * 10 + 5.0F, var9 + var5 / 2.0F, var10 - var5 / 2.0F);
               var3[1] = var11;
               var3[2] = Vector2.getDirection(var10 - var9, 0.0F);
    return true;
            }
         } else if (var1.h > 30 && var1.w < 15) {
            this.horizontalZone = false;
            this.zoneWidth = var1.w;
            if (var1.getWidth() < var4) {
               this.debugLine = "Vertical street is too small, w:" + var1.getWidth() + " h:" + var1.getHeight();
    return false;
            } else if (var1.getHeight() < var5) {
               this.debugLine = "Vertical street is too small, w:" + var1.getWidth() + " h:" + var1.getHeight();
    return false;
            } else if (var3 == nullptr) {
    return true;
            } else {
    float var6 = var1.getY();
    float var7 = var1.getY() + var1.getHeight();
    float var8 = var1.getX() + var1.getWidth() / 2.0F;
               var3[0] = var8;
               var3[1] = PZMath.clamp(var2.wy * 10 + 5.0F, var6 + var5 / 2.0F, var7 - var5 / 2.0F);
               var3[2] = Vector2.getDirection(0.0F, var6 - var7);
    return true;
            }
         } else {
            this.debugLine = "Zone too small or too large";
    return false;
         }
      }
   }

    bool getPolylineSpawnPoint(Zone var1, IsoChunk var2, float[] var3) {
      if (var1.isPolyline() && var1.polylineWidth > 0) {
    int var4 = this.getMinZoneWidth();
    int var5 = this.getMinZoneHeight();
         if (var1.polylineWidth < var4) {
            this.debugLine = "Polyline zone is too narrow, width:" + var1.polylineWidth;
    return false;
         } else {
            double[] var6 = new double[2];
    int var7 = var1.getClippedSegmentOfPolyline(var2.wx * 10, var2.wy * 10, (var2.wx + 1) * 10, (var2.wy + 1) * 10, var6);
            if (var7 == -1) {
    return false;
            } else {
    double var8 = var6[0];
    double var10 = var6[1];
    float var12 = var1.polylineWidth % 2 == 0 ? 0.0F : 0.5F;
    float var13 = var1.points.get(var7 * 2) + var12;
    float var14 = var1.points.get(var7 * 2 + 1) + var12;
    float var15 = var1.points.get(var7 * 2 + 2) + var12;
    float var16 = var1.points.get(var7 * 2 + 3) + var12;
    float var17 = var15 - var13;
    float var18 = var16 - var14;
    float var19 = Vector2f.length(var17, var18);
               if (var19 < var5) {
    return false;
               } else {
                  this.zoneWidth = var1.polylineWidth;
                  if (var3 == nullptr) {
    return true;
                  } else {
    float var20 = var5 / 2.0F / var19;
    float var21 = PZMath.max((float)var8 - var20, var20);
    float var22 = PZMath.min((float)var10 + var20, 1.0F - var20);
    float var23 = var13 + var17 * var21;
    float var24 = var14 + var18 * var21;
    float var25 = var13 + var17 * var22;
    float var26 = var14 + var18 * var22;
    float var27 = Rand.Next(0.0F, 1.0F);
                     if (Core.bDebug) {
                        var27 = (float)(System.currentTimeMillis() / 20L % 360L) / 360.0F;
                     }

                     var3[0] = var23 + (var25 - var23) * var27;
                     var3[1] = var24 + (var26 - var24) * var27;
                     var3[2] = Vector2.getDirection(var17, var18);
    return true;
                  }
               }
            }
         }
      } else {
    return false;
      }
   }

    bool isFullyStreamedIn(int var1, int var2, int var3, int var4) {
    uint8_t var5 = 10;
    int var6 = var1 / var5;
    int var7 = var2 / var5;
    int var8 = (var3 - 1) / var5;
    int var9 = (var4 - 1) / var5;

      for (int var10 = var7; var10 <= var9; var10++) {
         for (int var11 = var6; var11 <= var8; var11++) {
            if (!this.isChunkLoaded(var11, var10)) {
    return false;
            }
         }
      }

    return true;
   }

    bool isChunkLoaded(int var1, int var2) {
    IsoChunk var3 = GameServer.bServer ? ServerMap.instance.getChunk(var1, var2) : IsoWorld.instance.CurrentCell.getChunk(var1, var2);
      return var3 != nullptr && var3.bLoaded;
   }

    bool initVehicleStorySpawner(Zone var1, IsoChunk var2, bool var3) {
    return false;
   }

    bool callVehicleStorySpawner(Zone var1, IsoChunk var2, float var3) {
      float[] var4 = new float[3];
      if (!this.getSpawnPoint(var1, var2, var4)) {
    return false;
      } else {
         this.initVehicleStorySpawner(var1, var2, false);
    VehicleStorySpawner var5 = VehicleStorySpawner.getInstance();
    float var6 = var4[2];
         if (Rand.NextBool(2)) {
            var6 += (float) Math.PI;
         }

         var6 += var3;
         var5.spawn(var4[0], var4[1], 0.0F, ++var6, this::spawnElement);
    return true;
      }
   }

    void spawnElement(VehicleStorySpawner var1, Element var2) {
   }

   public BaseVehicle[] addSmashedOverlay(BaseVehicle var1, BaseVehicle var2, int var3, int var4, boolean var5, boolean var6) {
    IsoDirections var7 = var1.getDir();
    IsoDirections var8 = var2.getDir();
    void* var9 = nullptr;
    void* var10 = nullptr;
      if (!var5) {
         var9 = "Front";
         if (var8 == IsoDirections.W) {
            if (var7 == IsoDirections.S) {
               var10 = "Right";
            } else {
               var10 = "Left";
            }
         } else if (var7 == IsoDirections.S) {
            var10 = "Left";
         } else {
            var10 = "Right";
         }
      } else {
         if (var7 == IsoDirections.S) {
            if (var3 > 0) {
               var9 = "Left";
            } else {
               var9 = "Right";
            }
         } else if (var3 < 0) {
            var9 = "Left";
         } else {
            var9 = "Right";
         }

         var10 = "Front";
      }

      var1 = var1.setSmashed((std::string)var9);
      var2 = var2.setSmashed((std::string)var10);
      if (var6) {
         var1.setBloodIntensity((std::string)var9, 1.0F);
         var2.setBloodIntensity((std::string)var10, 1.0F);
      }

      return new BaseVehicle[]{var1, var2};
   }

    int getChance() {
      return this.chance;
   }

    void setChance(int var1) {
      this.chance = var1;
   }

    int getMinimumDays() {
      return this.minimumDays;
   }

    void setMinimumDays(int var1) {
      this.minimumDays = var1;
   }

    int getMaximumDays() {
      return this.maximumDays;
   }

    void setMaximumDays(int var1) {
      this.maximumDays = var1;
   }

    std::string getName() {
      return this.name;
   }

    std::string getDebugLine() {
      return this.debugLine;
   }

    void registerCustomOutfits() {
   }
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
