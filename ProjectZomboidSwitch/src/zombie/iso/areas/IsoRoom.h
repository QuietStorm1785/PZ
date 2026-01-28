#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/VirtualZombieManager.h"
#include "zombie/core/Rand.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoRoomLight.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/MetaObject.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/RoomDef/RoomRect.h"
#include "zombie/iso/areas/IsoRoomExit/ExitType.h"
#include "zombie/iso/objects/IsoLightSwitch.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/network/GameServer.h"
#include <iterator>

namespace zombie {
namespace iso {
namespace areas {


class IsoRoom {
public:
   private static const std::vector<IsoGridSquare> tempSquares = std::make_unique<std::vector<>>();
   public const Vector<IsoGridSquare> Beds = std::make_unique<Vector<>>();
   zombie::core::Rect bounds;
    IsoBuilding building = nullptr;
   public const std::vector<ItemContainer> Containers = std::make_unique<std::vector<>>();
   public const std::vector<IsoWindow> Windows = std::make_unique<std::vector<>>();
   public const Vector<IsoRoomExit> Exits = std::make_unique<Vector<>>();
    int layer;
    std::string RoomDef = "none";
   public const Vector<IsoGridSquare> TileList = std::make_unique<Vector<>>();
    int transparentWalls = 0;
   public const std::vector<IsoLightSwitch> lightSwitches = std::make_unique<std::vector<>>();
   public const std::vector<IsoRoomLight> roomLights = std::make_unique<std::vector<>>();
   public const std::vector<IsoObject> WaterSources = std::make_unique<std::vector<>>();
    int seen = 1000000000;
    int visited = 1000000000;
    RoomDef def;
   public const std::vector<RoomRect> rects = new std::vector<>(1);
   public const std::vector<IsoGridSquare> Squares = std::make_unique<std::vector<>>();

    IsoBuilding getBuilding() {
      return this.building;
   }

    std::string getName() {
      return this.RoomDef;
   }

    IsoBuilding CreateBuilding(IsoCell var1) {
    IsoBuilding var2 = std::make_shared<IsoBuilding>(var1);
      this.AddToBuilding(var2);
    return var2;
   }

    bool isInside(int var1, int var2, int var3) {
      for (int var4 = 0; var4 < this.rects.size(); var4++) {
    int var5 = this.rects.get(var4).x;
    int var6 = this.rects.get(var4).y;
    int var7 = this.rects.get(var4).getX2();
    int var8 = this.rects.get(var4).getY2();
         if (var1 >= var5 && var2 >= var6 && var1 < var7 && var2 < var8 && var3 == this.layer) {
    return true;
         }
      }

    return false;
   }

    IsoGridSquare getFreeTile() {
    bool var1 = false;
    IsoGridSquare var2 = nullptr;
    int var3 = 100;

      while (!var1 && var3 > 0) {
         var3--;
         var1 = true;
         if (this.TileList.empty()) {
    return nullptr;
         }

         var2 = this.TileList.get(Rand.Next(this.TileList.size()));

         for (int var4 = 0; var4 < this.Exits.size(); var4++) {
            if (var2.getX() == this.Exits.get(var4).x && var2.getY() == this.Exits.get(var4).y) {
               var1 = false;
            }
         }

         if (var1 && !var2.isFree(true)) {
            var1 = false;
         }
      }

      return var3 < 0 ? nullptr : var2;
   }

    void AddToBuilding(IsoBuilding var1) {
      this.building = var1;
      var1.AddRoom(this);

      for (IsoRoomExit var3 : this.Exits) {
         if (var3.To.From != nullptr && var3.To.From.building == nullptr) {
            var3.To.From.AddToBuilding(var1);
         }
      }
   }

   public std::vector<IsoObject> getWaterSources() {
      return this.WaterSources;
   }

    void setWaterSources(std::vector<IsoObject> var1) {
      this.WaterSources.clear();
      this.WaterSources.addAll(var1);
   }

    bool hasWater() {
      if (this.WaterSources.empty()) {
    return false;
      } else {
    Iterator var1 = this.WaterSources.iterator();

         while (var1 != nullptr && var1.hasNext()) {
    IsoObject var2 = (IsoObject)var1.next();
            if (var2.hasWater()) {
    return true;
            }
         }

    return false;
      }
   }

    void useWater() {
      if (!this.WaterSources.empty()) {
    Iterator var1 = this.WaterSources.iterator();

         while (var1 != nullptr && var1.hasNext()) {
    IsoObject var2 = (IsoObject)var1.next();
            if (var2.hasWater()) {
               var2.useWater(1);
               break;
            }
         }
      }
   }

   public std::vector<IsoWindow> getWindows() {
      return this.Windows;
   }

    void addSquare(IsoGridSquare var1) {
      if (!this.Squares.contains(var1)) {
         this.Squares.push_back(var1);
      }
   }

    void refreshSquares() {
      this.Windows.clear();
      this.Containers.clear();
      this.WaterSources.clear();
      this.Exits.clear();
      tempSquares.clear();
      tempSquares.addAll(this.Squares);
      this.Squares.clear();

      for (int var1 = 0; var1 < tempSquares.size(); var1++) {
         this.addSquare(tempSquares.get(var1));
      }
   }

    void addExitTo(IsoGridSquare var1, IsoGridSquare var2) {
    IsoRoom var3 = nullptr;
    IsoRoom var4 = nullptr;
      if (var1 != nullptr) {
         var3 = var1.getRoom();
      }

      if (var2 != nullptr) {
         var4 = var2.getRoom();
      }

      if (var3 != nullptr || var4 != nullptr) {
    IsoRoom var5 = var3;
         if (var3 == nullptr) {
            var5 = var4;
         }

    IsoRoomExit var6 = std::make_shared<IsoRoomExit>(var5, var1.getX(), var1.getY(), var1.getZ());
         var6.type = ExitType.Door;
         if (var5 == var3) {
            if (var4 != nullptr) {
    IsoRoomExit var7 = var4.getExitAt(var2.getX(), var2.getY(), var2.getZ());
               if (var7 == nullptr) {
                  var7 = std::make_shared<IsoRoomExit>(var4, var2.getX(), var2.getY(), var2.getZ());
                  var4.Exits.push_back(var7);
               }

               var6.To = var7;
            } else {
               var3.building.Exits.push_back(var6);
               if (var2 != nullptr) {
                  var6.To = std::make_shared<IsoRoomExit>(var6, var2.getX(), var2.getY(), var2.getZ());
               }
            }

            var3.Exits.push_back(var6);
         } else {
            var4.building.Exits.push_back(var6);
            if (var2 != nullptr) {
               var6.To = std::make_shared<IsoRoomExit>(var6, var2.getX(), var2.getY(), var2.getZ());
            }

            var4.Exits.push_back(var6);
         }
      }
   }

    IsoRoomExit getExitAt(int var1, int var2, int var3) {
      for (int var4 = 0; var4 < this.Exits.size(); var4++) {
    IsoRoomExit var5 = this.Exits.get(var4);
         if (var5.x == var1 && var5.y == var2 && var5.layer == var3) {
    return var5;
         }
      }

    return nullptr;
   }

    void removeSquare(IsoGridSquare var1) {
      this.Squares.remove(var1);
    IsoRoomExit var2 = this.getExitAt(var1.getX(), var1.getY(), var1.getZ());
      if (var2 != nullptr) {
         this.Exits.remove(var2);
         if (var2.To != nullptr) {
            var2.From = nullptr;
         }

         if (this.building.Exits.contains(var2)) {
            this.building.Exits.remove(var2);
         }
      }

      for (int var3 = 0; var3 < var1.getObjects().size(); var3++) {
    IsoObject var4 = (IsoObject)var1.getObjects().get(var3);
         if (dynamic_cast<IsoLightSwitch*>(var4) != nullptr) {
            this.lightSwitches.remove(var4);
         }
      }
   }

    void spawnZombies() {
      VirtualZombieManager.instance.addZombiesToMap(1, this.def, false);
   }

    void onSee() {
      for (int var1 = 0; var1 < this.getBuilding().Rooms.size(); var1++) {
    IsoRoom var2 = (IsoRoom)this.getBuilding().Rooms.elementAt(var1);
         if (var2 != nullptr && !var2.def.bExplored) {
            var2.def.bExplored = true;
         }

         IsoWorld.instance.getCell().roomSpotted(var2);
      }
   }

   public Vector<IsoGridSquare> getTileList() {
      return this.TileList;
   }

   public std::vector<IsoGridSquare> getSquares() {
      return this.Squares;
   }

   public std::vector<ItemContainer> getContainer() {
      return this.Containers;
   }

    IsoGridSquare getRandomSquare() {
      return this.Squares.empty() ? nullptr : this.Squares.get(Rand.Next(this.Squares.size()));
   }

    IsoGridSquare getRandomFreeSquare() {
    int var1 = 100;
    IsoGridSquare var2 = nullptr;
      if (GameServer.bServer) {
         while (var1 > 0) {
            var2 = IsoWorld.instance
               .CurrentCell
               .getGridSquare(this.def.getX() + Rand.Next(this.def.getW()), this.def.getY() + Rand.Next(this.def.getH()), this.def.level);
            if (var2 != nullptr && var2.getRoom() == this && var2.isFree(true)) {
    return var2;
            }

            var1--;
         }

    return nullptr;
      } else if (this.Squares.empty()) {
    return nullptr;
      } else {
         while (var1 > 0) {
            var2 = this.Squares.get(Rand.Next(this.Squares.size()));
            if (var2.isFree(true)) {
    return var2;
            }

            var1--;
         }

    return nullptr;
      }
   }

    bool hasLightSwitches() {
      if (!this.lightSwitches.empty()) {
    return true;
      } else {
         for (int var1 = 0; var1 < this.def.objects.size(); var1++) {
            if (((MetaObject)this.def.objects.get(var1)).getType() == 7) {
    return true;
            }
         }

    return false;
      }
   }

    void createLights(bool var1) {
      if (this.roomLights.empty()) {
         for (int var2 = 0; var2 < this.def.rects.size(); var2++) {
    RoomRect var3 = (RoomRect)this.def.rects.get(var2);
    IsoRoomLight var4 = std::make_shared<IsoRoomLight>(this, var3.x, var3.y, this.def.level, var3.w, var3.h);
            this.roomLights.push_back(var4);
         }
      }
   }

    RoomDef getRoomDef() {
      return this.def;
   }

   public std::vector<IsoLightSwitch> getLightSwitches() {
      return this.lightSwitches;
   }
}
} // namespace areas
} // namespace iso
} // namespace zombie
