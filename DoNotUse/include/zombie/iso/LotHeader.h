#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/map/hash/TLongObjectHashMap.h"
#include "zombie/iso/RoomDef/RoomRect.h"
#include "zombie/iso/areas/IsoBuilding.h"
#include "zombie/iso/areas/IsoRoom.h"
#include <algorithm>

namespace zombie {
namespace iso {


class LotHeader {
public:
    int cellX;
    int cellY;
    int width = 0;
    int height = 0;
    int levels = 0;
    int version = 0;
   public const std::unordered_map<int, RoomDef> Rooms = std::make_unique<std::unordered_map<>>();
   public const TLongObjectHashMap<RoomDef> RoomByMetaID = std::make_unique<TLongObjectHashMap>();
   public const std::vector<RoomDef> RoomList = std::make_unique<std::vector<>>();
   public const std::vector<BuildingDef> Buildings = std::make_unique<std::vector<>>();
   public const TLongObjectHashMap<BuildingDef> BuildingByMetaID = std::make_unique<TLongObjectHashMap>();
   public const std::unordered_map<int, IsoRoom> isoRooms = std::make_unique<std::unordered_map<>>();
   public const std::unordered_map<int, IsoBuilding> isoBuildings = std::make_unique<std::unordered_map<>>();
    bool bFixed2x;
   protected const std::vector<std::string> tilesUsed = std::make_unique<std::vector<>>();

    int getHeight() {
      return this.height;
   }

    int getWidth() {
      return this.width;
   }

    int getLevels() {
      return this.levels;
   }

    IsoRoom getRoom(int var1) {
    RoomDef var2 = this.Rooms.get(var1);
      if (!this.isoRooms.containsKey(var1)) {
    IsoRoom var3 = std::make_shared<IsoRoom>();
         var3.rects.addAll(var2.rects);
         var3.RoomDef = var2.name;
         var3.def = var2;
         var3.layer = var2.level;
         IsoWorld.instance.CurrentCell.getRoomList().push_back(var3);
         if (var2.building == nullptr) {
            var2.building = std::make_unique<BuildingDef>();
            var2.building.ID = this.Buildings.size();
            var2.building.rooms.push_back(var2);
            var2.building.CalculateBounds(std::make_unique<std::vector>());
            var2.building.metaID = var2.building.calculateMetaID(this.cellX, this.cellY);
            this.Buildings.push_back(var2.building);
         }

    int var4 = var2.building.ID;
         this.isoRooms.put(var1, var3);
         if (!this.isoBuildings.containsKey(var4)) {
            var3.building = std::make_unique<IsoBuilding>();
            var3.building.def = var2.building;
            this.isoBuildings.put(var4, var3.building);
            var3.building.CreateFrom(var2.building, this);
         } else {
            var3.building = this.isoBuildings.get(var4);
         }

    return var3;
      } else {
         return this.isoRooms.get(var1);
      }
   }

    int getRoomAt(int var1, int var2, int var3) {
      for (Entry var5 : this.Rooms.entrySet()) {
    RoomDef var6 = (RoomDef)var5.getValue();

         for (int var7 = 0; var7 < var6.rects.size(); var7++) {
    RoomRect var8 = (RoomRect)var6.rects.get(var7);
            if (var8.x <= var1 && var8.y <= var2 && var6.level == var3 && var8.getX2() > var1 && var8.getY2() > var2) {
               return (int)var5.getKey();
            }
         }
      }

      return -1;
   }

    void Dispose() {
      this.Rooms.clear();
      this.RoomByMetaID.clear();
      this.RoomList.clear();
      this.Buildings.clear();
      this.BuildingByMetaID.clear();
      this.isoRooms.clear();
      this.isoBuildings.clear();
      this.tilesUsed.clear();
   }
}
} // namespace iso
} // namespace zombie
