#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/array/TShortArrayList.h"
#include "org/joml/Vector2f.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/Rand.h"
#include "zombie/core/stash/StashSystem.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/RoomDef/RoomRect.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"

namespace zombie {
namespace iso {


class BuildingDef {
public:
   static const std::vector<IsoGridSquare> squareChoices = std::make_unique<std::vector<>>();
   public const std::vector<RoomDef> emptyoutside = std::make_unique<std::vector<>>();
    KahluaTable table = nullptr;
    bool seen = false;
    bool hasBeenVisited = false;
    std::string stash = nullptr;
    int lootRespawnHour = -1;
    TShortArrayList overlappedChunks;
    bool bAlarmed = false;
    int x = 10000000;
    int y = 10000000;
    int x2 = -10000000;
    int y2 = -10000000;
   public const std::vector<RoomDef> rooms = std::make_unique<std::vector<>>();
    Zone zone;
    int food;
   public std::vector<InventoryItem> items = std::make_unique<std::vector<>>();
   public std::unordered_set<std::string> itemTypes = std::make_unique<std::unordered_set<>>();
    int ID = 0;
    int keySpawned = 0;
    int keyId = -1;
    long metaID;

    public BuildingDef() {
      this.table = LuaManager.platform.newTable();
      this.setKeyId(Rand.Next(100000000));
   }

    KahluaTable getTable() {
      return this.table;
   }

   public std::vector<RoomDef> getRooms() {
      return this.rooms;
   }

    RoomDef getRoom(const std::string& var1) {
      for (int var2 = 0; var2 < this.rooms.size(); var2++) {
    RoomDef var3 = this.rooms.get(var2);
         if (var3.getName().equalsIgnoreCase(var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    bool isAllExplored() {
      for (int var1 = 0; var1 < this.rooms.size(); var1++) {
         if (!this.rooms.get(var1).bExplored) {
    return false;
         }
      }

    return true;
   }

    void setAllExplored(bool var1) {
      for (int var2 = 0; var2 < this.rooms.size(); var2++) {
    RoomDef var3 = this.rooms.get(var2);
         var3.setExplored(var1);
      }
   }

    RoomDef getFirstRoom() {
      return this.rooms.get(0);
   }

    int getChunkX() {
      return this.x / 10;
   }

    int getChunkY() {
      return this.y / 10;
   }

    int getX() {
      return this.x;
   }

    int getY() {
      return this.y;
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

    int getID() {
      return this.ID;
   }

    void refreshSquares() {
      for (int var1 = 0; var1 < this.rooms.size(); var1++) {
    RoomDef var2 = this.rooms.get(var1);
         var2.refreshSquares();
      }
   }

    void CalculateBounds(std::vector<RoomDef> var1) {
      for (int var2 = 0; var2 < this.rooms.size(); var2++) {
    RoomDef var3 = this.rooms.get(var2);

         for (int var4 = 0; var4 < var3.rects.size(); var4++) {
    RoomRect var5 = (RoomRect)var3.rects.get(var4);
            if (var5.x < this.x) {
               this.x = var5.x;
            }

            if (var5.y < this.y) {
               this.y = var5.y;
            }

            if (var5.x + var5.w > this.x2) {
               this.x2 = var5.x + var5.w;
            }

            if (var5.y + var5.h > this.y2) {
               this.y2 = var5.y + var5.h;
            }
         }
      }

      for (int var12 = 0; var12 < this.emptyoutside.size(); var12++) {
    RoomDef var15 = this.emptyoutside.get(var12);

         for (int var18 = 0; var18 < var15.rects.size(); var18++) {
    RoomRect var21 = (RoomRect)var15.rects.get(var18);
            if (var21.x < this.x) {
               this.x = var21.x;
            }

            if (var21.y < this.y) {
               this.y = var21.y;
            }

            if (var21.x + var21.w > this.x2) {
               this.x2 = var21.x + var21.w;
            }

            if (var21.y + var21.h > this.y2) {
               this.y2 = var21.y + var21.h;
            }
         }
      }

    int var13 = this.x / 10;
    int var16 = this.y / 10;
    int var19 = (this.x2 + 0) / 10;
    int var22 = (this.y2 + 0) / 10;
      this.overlappedChunks = std::make_shared<TShortArrayList>((var19 - var13 + 1) * (var22 - var16 + 1) * 2);
      this.overlappedChunks.clear();
      var1.clear();
      var1.addAll(this.rooms);
      var1.addAll(this.emptyoutside);

      for (int var6 = 0; var6 < var1.size(); var6++) {
    RoomDef var7 = (RoomDef)var1.get(var6);

         for (int var8 = 0; var8 < var7.rects.size(); var8++) {
    RoomRect var9 = (RoomRect)var7.rects.get(var8);
            var13 = var9.x / 10;
            var16 = var9.y / 10;
            var19 = (var9.x + var9.w + 0) / 10;
            var22 = (var9.y + var9.h + 0) / 10;

            for (int var10 = var16; var10 <= var22; var10++) {
               for (int var11 = var13; var11 <= var19; var11++) {
                  if (!this.overlapsChunk(var11, var10)) {
                     this.overlappedChunks.push_back((short)var11);
                     this.overlappedChunks.push_back((short)var10);
                  }
               }
            }
         }
      }
   }

    long calculateMetaID(int var1, int var2) {
    int var3 = int.MAX_VALUE;
    int var4 = int.MAX_VALUE;
    int var5 = int.MAX_VALUE;
    std::vector var6 = this.rooms.empty() ? this.emptyoutside : this.rooms;

      for (int var7 = 0; var7 < var6.size(); var7++) {
    RoomDef var8 = (RoomDef)var6.get(var7);
         if (var8.level <= var5) {
            if (var8.level < var5) {
               var3 = int.MAX_VALUE;
               var4 = int.MAX_VALUE;
            }

            var5 = var8.level;

            for (int var9 = 0; var9 < var8.rects.size(); var9++) {
    RoomRect var10 = (RoomRect)var8.rects.get(var9);
               if (var10.x <= var3 && var10.y < var4) {
                  var3 = var10.x;
                  var4 = var10.y;
               }
            }
         }
      }

      var3 -= var1 * 300;
      var4 -= var2 * 300;
      return (long)var5 << 32 | (long)var4 << 16 | var3;
   }

    void recalculate() {
      this.food = 0;
      this.items.clear();
      this.itemTypes.clear();

      for (int var1 = 0; var1 < this.rooms.size(); var1++) {
    IsoRoom var2 = this.rooms.get(var1).getIsoRoom();

         for (int var3 = 0; var3 < var2.Containers.size(); var3++) {
    ItemContainer var4 = (ItemContainer)var2.Containers.get(var3);

            for (int var5 = 0; var5 < var4.Items.size(); var5++) {
    InventoryItem var6 = (InventoryItem)var4.Items.get(var5);
               this.items.push_back(var6);
               this.itemTypes.push_back(var6.getFullType());
               if (dynamic_cast<Food*>(var6) != nullptr) {
                  this.food++;
               }
            }
         }
      }
   }

    bool overlapsChunk(int var1, int var2) {
      for (byte var3 = 0; var3 < this.overlappedChunks.size(); var3 += 2) {
         if (var1 == this.overlappedChunks.get(var3) && var2 == this.overlappedChunks.get(var3 + 1)) {
    return true;
         }
      }

    return false;
   }

    IsoGridSquare getFreeSquareInRoom() {
      squareChoices.clear();

      for (int var1 = 0; var1 < this.rooms.size(); var1++) {
    RoomDef var2 = this.rooms.get(var1);

         for (int var3 = 0; var3 < var2.rects.size(); var3++) {
    RoomRect var4 = (RoomRect)var2.rects.get(var3);

            for (int var5 = var4.getX(); var5 < var4.getX2(); var5++) {
               for (int var6 = var4.getY(); var6 < var4.getY2(); var6++) {
    IsoGridSquare var7 = IsoWorld.instance.CurrentCell.getGridSquare(var5, var6, var2.getZ());
                  if (var7 != nullptr && var7.isFree(false)) {
                     squareChoices.push_back(var7);
                  }
               }
            }
         }
      }

      return !squareChoices.empty() ? squareChoices.get(Rand.Next(squareChoices.size())) : nullptr;
   }

    bool containsRoom(const std::string& var1) {
      for (int var2 = 0; var2 < this.rooms.size(); var2++) {
    RoomDef var3 = this.rooms.get(var2);
         if (var3.name == var1)) {
    return true;
         }
      }

    return false;
   }

    bool isFullyStreamedIn() {
      for (byte var1 = 0; var1 < this.overlappedChunks.size(); var1 += 2) {
    short var2 = this.overlappedChunks.get(var1);
    short var3 = this.overlappedChunks.get(var1 + 1);
    IsoChunk var4 = GameServer.bServer ? ServerMap.instance.getChunk(var2, var3) : IsoWorld.instance.CurrentCell.getChunk(var2, var3);
         if (var4 == nullptr) {
    return false;
         }
      }

    return true;
   }

    bool isAnyChunkNewlyLoaded() {
      for (byte var1 = 0; var1 < this.overlappedChunks.size(); var1 += 2) {
    short var2 = this.overlappedChunks.get(var1);
    short var3 = this.overlappedChunks.get(var1 + 1);
    IsoChunk var4 = GameServer.bServer ? ServerMap.instance.getChunk(var2, var3) : IsoWorld.instance.CurrentCell.getChunk(var2, var3);
         if (var4 == nullptr) {
    return false;
         }

         if (var4.isNewChunk()) {
    return true;
         }
      }

    return false;
   }

    Zone getZone() {
      return this.zone;
   }

    int getKeyId() {
      return this.keyId;
   }

    void setKeyId(int var1) {
      this.keyId = var1;
   }

    int getKeySpawned() {
      return this.keySpawned;
   }

    void setKeySpawned(int var1) {
      this.keySpawned = var1;
   }

    bool isHasBeenVisited() {
      return this.hasBeenVisited;
   }

    void setHasBeenVisited(bool var1) {
      if (var1 && !this.hasBeenVisited) {
         StashSystem.visitedBuilding(this);
      }

      this.hasBeenVisited = var1;
   }

    bool isAlarmed() {
      return this.bAlarmed;
   }

    void setAlarmed(bool var1) {
      this.bAlarmed = var1;
   }

    RoomDef getRandomRoom(int var1) {
    RoomDef var2 = this.getRooms().get(Rand.Next(0, this.getRooms().size()));
      if (var1 > 0 && var2.area >= var1) {
    return var2;
      } else {
    int var3 = 0;

         while (var3 <= 20) {
            var3++;
            var2 = this.getRooms().get(Rand.Next(0, this.getRooms().size()));
            if (var2.area >= var1) {
    return var2;
            }
         }

    return var2;
      }
   }

    float getClosestPoint(float var1, float var2, Vector2f var3) {
    float var4 = float.MAX_VALUE;
    Vector2f var5 = std::make_shared<Vector2f>();

      for (int var6 = 0; var6 < this.rooms.size(); var6++) {
    RoomDef var7 = this.rooms.get(var6);
    float var8 = var7.getClosestPoint(var1, var2, var5);
         if (var8 < var4) {
            var4 = var8;
            var3.set(var5);
         }
      }

    return var4;
   }

    void Dispose() {
      for (RoomDef var2 : this.rooms) {
         var2.Dispose();
      }

      this.emptyoutside.clear();
      this.rooms.clear();
   }
}
} // namespace iso
} // namespace zombie
