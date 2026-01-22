#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector2f.h"
#include "zombie/iso/RoomDef/RoomRect.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>

namespace zombie {
namespace iso {


class RoomDef {
public:
   private static const std::vector<IsoGridSquare> squareChoices = std::make_unique<std::vector<>>();
    bool bExplored = false;
    bool bDoneSpawn = false;
    int IndoorZombies = 0;
    int spawnCount = -1;
    bool bLightsActive = false;
    std::string name;
    int level;
    BuildingDef building;
    int ID = -1;
   public const std::vector<RoomRect> rects = new std::vector<>(1);
   public const std::vector<MetaObject> objects = new std::vector<>(0);
    int x = 100000;
    int y = 100000;
    int x2 = -10000;
    int y2 = -10000;
    int area;
   private const std::unordered_map<std::string, int> proceduralSpawnedContainer = std::make_unique<std::unordered_map<>>();
    bool roofFixed = false;
    long metaID;

    public RoomDef(int var1, const std::string& var2) {
      this.ID = var1;
      this.name = var2;
   }

    int getID() {
      return this.ID;
   }

    bool isExplored() {
      return this.bExplored;
   }

    bool isInside(int var1, int var2, int var3) {
    int var4 = this.building.x;
    int var5 = this.building.y;

      for (int var6 = 0; var6 < this.rects.size(); var6++) {
    int var7 = this.rects.get(var6).x;
    int var8 = this.rects.get(var6).y;
    int var9 = this.rects.get(var6).getX2();
    int var10 = this.rects.get(var6).getY2();
         if (var1 >= var7 && var2 >= var8 && var1 < var9 && var2 < var10 && var3 == this.level) {
    return true;
         }
      }

    return false;
   }

    bool intersects(int var1, int var2, int var3, int var4) {
      for (int var5 = 0; var5 < this.rects.size(); var5++) {
    RoomRect var6 = this.rects.get(var5);
         if (var1 + var3 > var6.getX() && var1 < var6.getX2() && var2 + var4 > var6.getY() && var2 < var6.getY2()) {
    return true;
         }
      }

    return false;
   }

    float getAreaOverlapping(IsoChunk var1) {
      return this.getAreaOverlapping(var1.wx * 10, var1.wy * 10, 10, 10);
   }

    float getAreaOverlapping(int var1, int var2, int var3, int var4) {
    int var5 = 0;
    int var6 = 0;

      for (int var7 = 0; var7 < this.rects.size(); var7++) {
    RoomRect var8 = this.rects.get(var7);
         var5 += var8.w * var8.h;
    int var9 = Math.max(var1, var8.x);
    int var10 = Math.max(var2, var8.y);
    int var11 = Math.min(var1 + var3, var8.x + var8.w);
    int var12 = Math.min(var2 + var4, var8.y + var8.h);
         if (var11 >= var9 && var12 >= var10) {
            var6 += (var11 - var9) * (var12 - var10);
         }
      }

      return var6 <= 0 ? 0.0F : (float)var6 / var5;
   }

    void forEachChunk(IsoChunk> var1) {
    std::unordered_set var2 = new std::unordered_set();

      for (int var3 = 0; var3 < this.rects.size(); var3++) {
    RoomRect var4 = this.rects.get(var3);
    int var5 = var4.x / 10;
    int var6 = var4.y / 10;
    int var7 = (var4.x + var4.w) / 10;
    int var8 = (var4.y + var4.h) / 10;
         if ((var4.x + var4.w) % 10 == 0) {
            var7--;
         }

         if ((var4.y + var4.h) % 10 == 0) {
            var8--;
         }

         for (int var9 = var6; var9 <= var8; var9++) {
            for (int var10 = var5; var10 <= var7; var10++) {
    IsoChunk var11 = GameServer.bServer ? ServerMap.instance.getChunk(var10, var9) : IsoWorld.instance.CurrentCell.getChunk(var10, var9);
               if (var11 != nullptr) {
                  var2.push_back(var11);
               }
            }
         }
      }

      var2.forEach(var2x -> var1.accept(this, var2x));
      var2.clear();
   }

    IsoRoom getIsoRoom() {
      return IsoWorld.instance.MetaGrid.getMetaGridFromTile(this.x, this.y).info.getRoom(this.ID);
   }

   public std::vector<MetaObject> getObjects() {
      return this.objects;
   }

   public std::vector<MetaObject> getMetaObjects() {
      return this.objects;
   }

    void refreshSquares() {
      this.getIsoRoom().refreshSquares();
   }

    BuildingDef getBuilding() {
      return this.building;
   }

    void setBuilding(BuildingDef var1) {
      this.building = var1;
   }

    std::string getName() {
      return this.name;
   }

   public std::vector<RoomRect> getRects() {
      return this.rects;
   }

    int getY() {
      return this.y;
   }

    int getX() {
      return this.x;
   }

    int getX2() {
      return this.x2;
   }

    int getY2() {
      return this.y2;
   }

    int getW() {
      return this.x2 - this.x;
   }

    int getH() {
      return this.y2 - this.y;
   }

    int getZ() {
      return this.level;
   }

    void CalculateBounds() {
      for (int var1 = 0; var1 < this.rects.size(); var1++) {
    RoomRect var2 = this.rects.get(var1);
         if (var2.x < this.x) {
            this.x = var2.x;
         }

         if (var2.y < this.y) {
            this.y = var2.y;
         }

         if (var2.x + var2.w > this.x2) {
            this.x2 = var2.x + var2.w;
         }

         if (var2.y + var2.h > this.y2) {
            this.y2 = var2.y + var2.h;
         }

         this.area = this.area + var2.w * var2.h;
      }
   }

    long calculateMetaID(int var1, int var2) {
    int var3 = int.MAX_VALUE;
    int var4 = int.MAX_VALUE;

      for (int var5 = 0; var5 < this.rects.size(); var5++) {
    RoomRect var6 = this.rects.get(var5);
         if (var6.x <= var3 && var6.y < var4) {
            var3 = var6.x;
            var4 = var6.y;
         }
      }

      var3 -= var1 * 300;
      var4 -= var2 * 300;
      return (long)this.level << 32 | (long)var4 << 16 | var3;
   }

    int getArea() {
      return this.area;
   }

    void setExplored(bool var1) {
      this.bExplored = var1;
   }

    IsoGridSquare getFreeSquare() {
      return this.getRandomSquare(var0 -> var0.isFree(false));
   }

    IsoGridSquare getRandomSquare(Predicate<IsoGridSquare> var1) {
      squareChoices.clear();

      for (int var2 = 0; var2 < this.rects.size(); var2++) {
    RoomRect var3 = this.rects.get(var2);

         for (int var4 = var3.getX(); var4 < var3.getX2(); var4++) {
            for (int var5 = var3.getY(); var5 < var3.getY2(); var5++) {
    IsoGridSquare var6 = IsoWorld.instance.CurrentCell.getGridSquare(var4, var5, this.getZ());
               if (var6 != nullptr && var1 != nullptr && var1.test(var6) || var1 == nullptr) {
                  squareChoices.push_back(var6);
               }
            }
         }
      }

      return (IsoGridSquare)PZArrayUtil.pickRandom(squareChoices);
   }

    bool isEmptyOutside() {
      return "emptyoutside".equalsIgnoreCase(this.name);
   }

   public std::unordered_map<std::string, int> getProceduralSpawnedContainer() {
      return this.proceduralSpawnedContainer;
   }

    bool isRoofFixed() {
      return this.roofFixed;
   }

    void setRoofFixed(bool var1) {
      this.roofFixed = var1;
   }

    float getClosestPoint(float var1, float var2, Vector2f var3) {
    float var4 = float.MAX_VALUE;
    Vector2f var5 = std::make_shared<Vector2f>();

      for (int var6 = 0; var6 < this.rects.size(); var6++) {
    RoomRect var7 = this.rects.get(var6);
    float var8 = var7.getClosestPoint(var1, var2, var5);
         if (var8 < var4) {
            var4 = var8;
            var3.set(var5);
         }
      }

    return var4;
   }

    void Dispose() {
      this.building = nullptr;
      this.rects.clear();
      this.objects.clear();
      this.proceduralSpawnedContainer.clear();
   }
}
} // namespace iso
} // namespace zombie
