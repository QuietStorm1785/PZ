#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/array/TIntArrayList.h"
#include "java/awt/Rectangle.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/MapGroups.h"
#include "zombie/SandboxOptions.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/characters/Faction.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoGameCharacter/Location.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/stash/StashSystem.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/gameStates/ChooseGameInfo/Map.h"
#include "zombie/iso/IsoMetaGrid/MetaGridLoaderThread.h"
#include "zombie/iso/IsoMetaGrid/RoomTone.h"
#include "zombie/iso/IsoMetaGrid/VehicleZone.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/IsoMetaGrid/ZoneGeometryType.h"
#include "zombie/iso/areas/NonPvpZone.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/iso/objects/IsoMannequin/MannequinZone.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBBasic.h"
#include "zombie/util/SharedStrings.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/Clipper.h"
#include "zombie/vehicles/ClipperOffset.h"
#include "zombie/vehicles/ClipperOffset/EndType.h"
#include "zombie/vehicles/ClipperOffset/JoinType.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {


class IsoMetaGrid {
public:
    static const int NUM_LOADER_THREADS = 8;
   private static std::vector<std::string> s_PreferredZoneTypes = std::make_unique<std::vector<>>();
    static Clipper s_clipper = nullptr;
    static ClipperOffset s_clipperOffset = nullptr;
    static ByteBuffer s_clipperBuffer = nullptr;
   private static const ThreadLocal<Location> TL_Location = ThreadLocal.withInitial(Location::new);
   private static const ThreadLocal<std::vector<Zone>> TL_ZoneList = ThreadLocal.withInitial(std::vector::new);
    static Rectangle a = std::make_shared<Rectangle>();
    static Rectangle b = std::make_shared<Rectangle>();
   static std::vector<RoomDef> roomChoices = new std::vector<>(50);
   private const std::vector<RoomDef> tempRooms = std::make_unique<std::vector<>>();
   private const std::vector<Zone> tempZones1 = std::make_unique<std::vector<>>();
   private const std::vector<Zone> tempZones2 = std::make_unique<std::vector<>>();
   private const MetaGridLoaderThread[] threads = new MetaGridLoaderThread[8];
    int minX = 10000000;
    int minY = 10000000;
    int maxX = -10000000;
    int maxY = -10000000;
   public const std::vector<Zone> Zones = std::make_unique<std::vector<>>();
   public const std::vector<BuildingDef> Buildings = std::make_unique<std::vector<>>();
   public const std::vector<VehicleZone> VehiclesZones = std::make_unique<std::vector<>>();
   public IsoMetaCell[][] Grid;
   public const std::vector<IsoGameCharacter> MetaCharacters = std::make_unique<std::vector<>>();
   const std::vector<Vector2> HighZombieList = std::make_unique<std::vector<>>();
    int width;
    int height;
    const SharedStrings sharedStrings = std::make_shared<SharedStrings>();
    long createStartTime;

    void AddToMeta(IsoGameCharacter var1) {
      IsoWorld.instance.CurrentCell.Remove(var1);
      if (!this.MetaCharacters.contains(var1)) {
         this.MetaCharacters.push_back(var1);
      }
   }

    void RemoveFromMeta(IsoPlayer var1) {
      this.MetaCharacters.remove(var1);
      if (!IsoWorld.instance.CurrentCell.getObjectList().contains(var1)) {
         IsoWorld.instance.CurrentCell.getObjectList().push_back(var1);
      }
   }

    int getMinX() {
      return this.minX;
   }

    int getMinY() {
      return this.minY;
   }

    int getMaxX() {
      return this.maxX;
   }

    int getMaxY() {
      return this.maxY;
   }

    Zone getZoneAt(int var1, int var2, int var3) {
    IsoMetaChunk var4 = this.getChunkDataFromTile(var1, var2);
      return var4 != nullptr ? var4.getZoneAt(var1, var2, var3) : nullptr;
   }

   public std::vector<Zone> getZonesAt(int var1, int var2, int var3) {
      return this.getZonesAt(var1, var2, var3, std::make_unique<std::vector<>>());
   }

   public std::vector<Zone> getZonesAt(int var1, int var2, int var3, std::vector<Zone> var4) {
    IsoMetaChunk var5 = this.getChunkDataFromTile(var1, var2);
      return var5 != nullptr ? var5.getZonesAt(var1, var2, var3, var4) : var4;
   }

   public std::vector<Zone> getZonesIntersecting(int var1, int var2, int var3, int var4, int var5) {
    std::vector var6 = new std::vector();
      return this.getZonesIntersecting(var1, var2, var3, var4, var5, var6);
   }

   public std::vector<Zone> getZonesIntersecting(int var1, int var2, int var3, int var4, int var5, std::vector<Zone> var6) {
      for (int var7 = var2 / 300; var7 <= (var2 + var5) / 300; var7++) {
         for (int var8 = var1 / 300; var8 <= (var1 + var4) / 300; var8++) {
            if (var8 >= this.minX && var8 <= this.maxX && var7 >= this.minY && var7 <= this.maxY && this.Grid[var8 - this.minX][var7 - this.minY] != nullptr) {
               this.Grid[var8 - this.minX][var7 - this.minY].getZonesIntersecting(var1, var2, var3, var4, var5, var6);
            }
         }
      }

    return var6;
   }

    Zone getZoneWithBoundsAndType(int var1, int var2, int var3, int var4, int var5, const std::string& var6) {
    std::vector var7 = TL_ZoneList.get();
      var7.clear();
      this.getZonesIntersecting(var1, var2, var3, var4, var5, var7);

      for (int var8 = 0; var8 < var7.size(); var8++) {
    Zone var9 = (Zone)var7.get(var8);
         if (var9.x == var1 && var9.y == var2 && var9.z == var3 && var9.w == var4 && var9.h == var5 && StringUtils.equalsIgnoreCase(var9.type, var6)) {
    return var9;
         }
      }

    return nullptr;
   }

    VehicleZone getVehicleZoneAt(int var1, int var2, int var3) {
    IsoMetaCell var4 = this.getMetaGridFromTile(var1, var2);
      if (var4 != nullptr && !var4.vehicleZones.empty()) {
         for (int var5 = 0; var5 < var4.vehicleZones.size(); var5++) {
    VehicleZone var6 = (VehicleZone)var4.vehicleZones.get(var5);
            if (var6.contains(var1, var2, var3)) {
    return var6;
            }
         }

    return nullptr;
      } else {
    return nullptr;
      }
   }

    BuildingDef getBuildingAt(int var1, int var2) {
      for (int var3 = 0; var3 < this.Buildings.size(); var3++) {
    BuildingDef var4 = this.Buildings.get(var3);
         if (var4.x <= var1 && var4.y <= var2 && var4.getW() > var1 - var4.x && var4.getH() > var2 - var4.y) {
    return var4;
         }
      }

    return nullptr;
   }

    BuildingDef getBuildingAtRelax(int var1, int var2) {
      for (int var3 = 0; var3 < this.Buildings.size(); var3++) {
    BuildingDef var4 = this.Buildings.get(var3);
         if (var4.x <= var1 + 1 && var4.y <= var2 + 1 && var4.getW() > var1 - var4.x - 1 && var4.getH() > var2 - var4.y - 1) {
    return var4;
         }
      }

    return nullptr;
   }

    RoomDef getRoomAt(int var1, int var2, int var3) {
    IsoMetaChunk var4 = this.getChunkDataFromTile(var1, var2);
      return var4 != nullptr ? var4.getRoomAt(var1, var2, var3) : nullptr;
   }

    RoomDef getEmptyOutsideAt(int var1, int var2, int var3) {
    IsoMetaChunk var4 = this.getChunkDataFromTile(var1, var2);
      return var4 != nullptr ? var4.getEmptyOutsideAt(var1, var2, var3) : nullptr;
   }

    void getRoomsIntersecting(int var1, int var2, int var3, int var4, std::vector<RoomDef> var5) {
      for (int var6 = var2 / 300; var6 <= (var2 + this.height) / 300; var6++) {
         for (int var7 = var1 / 300; var7 <= (var1 + this.width) / 300; var7++) {
            if (var7 >= this.minX && var7 <= this.maxX && var6 >= this.minY && var6 <= this.maxY) {
    IsoMetaCell var8 = this.Grid[var7 - this.minX][var6 - this.minY];
               if (var8 != nullptr) {
                  var8.getRoomsIntersecting(var1, var2, var3, var4, var5);
               }
            }
         }
      }
   }

    int countRoomsIntersecting(int var1, int var2, int var3, int var4) {
      this.tempRooms.clear();

      for (int var5 = var2 / 300; var5 <= (var2 + this.height) / 300; var5++) {
         for (int var6 = var1 / 300; var6 <= (var1 + this.width) / 300; var6++) {
            if (var6 >= this.minX && var6 <= this.maxX && var5 >= this.minY && var5 <= this.maxY) {
    IsoMetaCell var7 = this.Grid[var6 - this.minX][var5 - this.minY];
               if (var7 != nullptr) {
                  var7.getRoomsIntersecting(var1, var2, var3, var4, this.tempRooms);
               }
            }
         }
      }

      return this.tempRooms.size();
   }

    int countNearbyBuildingsRooms(IsoPlayer var1) {
    int var2 = (int)var1.getX() - 20;
    int var3 = (int)var1.getY() - 20;
    uint8_t var4 = 40;
    uint8_t var5 = 40;
      return this.countRoomsIntersecting(var2, var3, var4, var5);
   }

    bool isInside(Zone var1, BuildingDef var2) {
      a.x = var1.x;
      a.y = var1.y;
      a.width = var1.w;
      a.height = var1.h;
      b.x = var2.x;
      b.y = var2.y;
      b.width = var2.getW();
      b.height = var2.getH();
      return a.contains(b);
   }

    bool isAdjacent(Zone var1, Zone var2) {
      if (var1 == var2) {
    return false;
      } else {
         a.x = var1.x;
         a.y = var1.y;
         a.width = var1.w;
         a.height = var1.h;
         b.x = var2.x;
         b.y = var2.y;
         b.width = var2.w;
         b.height = var2.h;
         a.x--;
         a.y--;
         a.width += 2;
         a.height += 2;
         b.x--;
         b.y--;
         b.width += 2;
         b.height += 2;
         return a.intersects(b);
      }
   }

    Zone registerZone(const std::string& var1, const std::string& var2, int var3, int var4, int var5, int var6, int var7) {
      return this.registerZone(var1, var2, var3, var4, var5, var6, var7, ZoneGeometryType.INVALID, nullptr, 0);
   }

    Zone registerZone(const std::string& var1, const std::string& var2, int var3, int var4, int var5, int var6, int var7, ZoneGeometryType var8, TIntArrayList var9, int var10) {
      var1 = this.sharedStrings.get(var1);
      var2 = this.sharedStrings.get(var2);
    Zone var11 = std::make_shared<Zone>(var1, var2, var3, var4, var5, var6, var7);
      var11.geometryType = var8;
      if (var9 != nullptr) {
         var11.points.addAll(var9);
         var11.polylineWidth = var10;
      }

      var11.isPreferredZoneForSquare = isPreferredZoneForSquare(var2);
      if (var3 >= this.minX * 300 - 100
         && var4 >= this.minY * 300 - 100
         && var3 + var6 <= (this.maxX + 1) * 300 + 100
         && var4 + var7 <= (this.maxY + 1) * 300 + 100
         && var5 >= 0
         && var5 < 8
         && var6 <= 600
         && var7 <= 600) {
         this.addZone(var11);
    return var11;
      } else {
    return var11;
      }
   }

    Zone registerGeometryZone(const std::string& var1, const std::string& var2, int var3, const std::string& var4, KahluaTable var5, KahluaTable var6) {
    int var7 = int.MAX_VALUE;
    int var8 = int.MAX_VALUE;
    int var9 = int.MIN_VALUE;
    int var10 = int.MIN_VALUE;
    TIntArrayList var11 = std::make_shared<TIntArrayList>(var5.len());

      for (byte var12 = 0; var12 < var5.len(); var12 += 2) {
    void* var13 = var5.rawget(var12 + 1);
    void* var14 = var5.rawget(var12 + 2);
    int var15 = ((double)var13).intValue();
    int var16 = ((double)var14).intValue();
         var11.push_back(var15);
         var11.push_back(var16);
         var7 = Math.min(var7, var15);
         var8 = Math.min(var8, var16);
         var9 = Math.max(var9, var15);
         var10 = Math.max(var10, var16);
      }
      ZoneGeometryType var17 = switch (var4) {
         case "point" -> ZoneGeometryType.Point;
         case "polygon" -> ZoneGeometryType.Polygon;
         case "polyline" -> ZoneGeometryType.Polyline;
         default -> throw IllegalArgumentException("unknown zone geometry type");
      };
    double var18 = var17 == ZoneGeometryType.Polyline && var6 != nullptr ? (double)Type.tryCastTo(var6.rawget("LineWidth"), double.class) : nullptr;
      if (var18 != nullptr) {
         int[] var20 = new int[4];
         this.calculatePolylineOutlineBounds(var11, var18.intValue(), var20);
         var7 = var20[0];
         var8 = var20[1];
         var9 = var20[2];
         var10 = var20[3];
      }

      if (!var2 == "Vehicle") && !var2 == "ParkingStall")) {
    Zone var22 = this.registerZone(var1, var2, var7, var8, var3, var9 - var7 + 1, var10 - var8 + 1, var17, var11, var18 == nullptr ? 0 : var18.intValue());
         var11.clear();
    return var22;
      } else {
    Zone var21 = this.registerVehiclesZone(var1, var2, var7, var8, var3, var9 - var7 + 1, var10 - var8 + 1, var6);
         if (var21 != nullptr) {
            var21.geometryType = var17;
            var21.points.addAll(var11);
            var21.polylineWidth = var18 == nullptr ? 0 : var18.intValue();
         }

    return var21;
      }
   }

    void calculatePolylineOutlineBounds(TIntArrayList var1, int var2, int[] var3) {
      if (s_clipperOffset == nullptr) {
         s_clipperOffset = std::make_unique<ClipperOffset>();
         s_clipperBuffer = ByteBuffer.allocateDirect(3072);
      }

      s_clipperOffset.clear();
      s_clipperBuffer.clear();
    float var4 = var2 % 2 == 0 ? 0.0F : 0.5F;

      for (byte var5 = 0; var5 < var1.size(); var5 += 2) {
    int var6 = var1.get(var5);
    int var7 = var1.get(var5 + 1);
         s_clipperBuffer.putFloat(var6 + var4);
         s_clipperBuffer.putFloat(var7 + var4);
      }

      s_clipperBuffer.flip();
      s_clipperOffset.addPath(var1.size() / 2, s_clipperBuffer, JoinType.jtMiter.ordinal(), EndType.etOpenButt.ordinal());
      s_clipperOffset.execute(var2 / 2.0F);
    int var14 = s_clipperOffset.getPolygonCount();
      if (var14 < 1) {
         DebugLog.General.warn("Failed to generate polyline outline");
      } else {
         s_clipperBuffer.clear();
         s_clipperOffset.getPolygon(0, s_clipperBuffer);
    short var15 = s_clipperBuffer.getShort();
    float var16 = float.MAX_VALUE;
    float var8 = float.MAX_VALUE;
    float var9 = -float.MAX_VALUE;
    float var10 = -float.MAX_VALUE;

         for (int var11 = 0; var11 < var15; var11++) {
    float var12 = s_clipperBuffer.getFloat();
    float var13 = s_clipperBuffer.getFloat();
            var16 = PZMath.min(var16, var12);
            var8 = PZMath.min(var8, var13);
            var9 = PZMath.max(var9, var12);
            var10 = PZMath.max(var10, var13);
         }

         var3[0] = (int)PZMath.floor(var16);
         var3[1] = (int)PZMath.floor(var8);
         var3[2] = (int)PZMath.ceil(var9);
         var3[3] = (int)PZMath.ceil(var10);
      }
   }

    Zone registerZoneNoOverlap(const std::string& var1, const std::string& var2, int var3, int var4, int var5, int var6, int var7) {
      return var3 >= this.minX * 300 - 100
            && var4 >= this.minY * 300 - 100
            && var3 + var6 <= (this.maxX + 1) * 300 + 100
            && var4 + var7 <= (this.maxY + 1) * 300 + 100
            && var5 >= 0
            && var5 < 8
            && var6 <= 600
            && var7 <= 600
         ? this.registerZone(var1, var2, var3, var4, var5, var6, var7)
         : nullptr;
   }

    void addZone(Zone var1) {
      this.Zones.push_back(var1);

      for (int var2 = var1.y / 300; var2 <= (var1.y + var1.h) / 300; var2++) {
         for (int var3 = var1.x / 300; var3 <= (var1.x + var1.w) / 300; var3++) {
            if (var3 >= this.minX && var3 <= this.maxX && var2 >= this.minY && var2 <= this.maxY && this.Grid[var3 - this.minX][var2 - this.minY] != nullptr) {
               this.Grid[var3 - this.minX][var2 - this.minY].addZone(var1, var3 * 300, var2 * 300);
            }
         }
      }
   }

    void removeZone(Zone var1) {
      this.Zones.remove(var1);

      for (int var2 = var1.y / 300; var2 <= (var1.y + var1.h) / 300; var2++) {
         for (int var3 = var1.x / 300; var3 <= (var1.x + var1.w) / 300; var3++) {
            if (var3 >= this.minX && var3 <= this.maxX && var2 >= this.minY && var2 <= this.maxY && this.Grid[var3 - this.minX][var2 - this.minY] != nullptr) {
               this.Grid[var3 - this.minX][var2 - this.minY].removeZone(var1);
            }
         }
      }
   }

    void removeZonesForCell(int var1, int var2) {
    IsoMetaCell var3 = this.getCellData(var1, var2);
      if (var3 != nullptr) {
    std::vector var4 = this.tempZones1;
         var4.clear();

         for (int var5 = 0; var5 < 900; var5++) {
            var3.ChunkMap[var5].getZonesIntersecting(var1 * 300, var2 * 300, 0, 300, 300, var4);
         }

         for (int var9 = 0; var9 < var4.size(); var9++) {
    Zone var6 = (Zone)var4.get(var9);
    std::vector var7 = this.tempZones2;
            if (var6.difference(var1 * 300, var2 * 300, 0, 300, 300, var7)) {
               this.removeZone(var6);

               for (int var8 = 0; var8 < var7.size(); var8++) {
                  this.addZone((Zone)var7.get(var8));
               }
            }
         }

         if (!var3.vehicleZones.empty()) {
            var3.vehicleZones.clear();
         }

         if (!var3.mannequinZones.empty()) {
            var3.mannequinZones.clear();
         }
      }
   }

    void removeZonesForLotDirectory(const std::string& var1) {
      if (!this.Zones.empty()) {
    File var2 = std::make_shared<File>(ZomboidFileSystem.instance.getString("media/maps/" + var1 + "/"));
         if (var2.isDirectory()) {
    std::unordered_map var3 = ChooseGameInfo.getMapDetails(var1);
            if (var3 != nullptr) {
               std::string[] var4 = var2.list();
               if (var4 != nullptr) {
                  for (int var5 = 0; var5 < var4.length; var5++) {
    std::string var6 = var4[var5];
                     if (var6.endsWith(".lotheader")) {
                        std::string[] var7 = var6.split("_");
                        var7[1] = var7[1].replace(".lotheader", "");
    int var8 = int.parseInt(var7[0].trim());
    int var9 = int.parseInt(var7[1].trim());
                        this.removeZonesForCell(var8, var9);
                     }
                  }
               }
            }
         }
      }
   }

    void processZones() {
    int var1 = 0;

      for (int var2 = this.minX; var2 <= this.maxX; var2++) {
         for (int var3 = this.minY; var3 <= this.maxY; var3++) {
            if (this.Grid[var2 - this.minX][var3 - this.minY] != nullptr) {
               for (int var4 = 0; var4 < 30; var4++) {
                  for (int var5 = 0; var5 < 30; var5++) {
                     var1 = Math.max(var1, this.Grid[var2 - this.minX][var3 - this.minY].getChunk(var5, var4).numZones());
                  }
               }
            }
         }
      }

      DebugLog.log("Max #ZONES on one chunk is " + var1);
   }

    Zone registerVehiclesZone(const std::string& var1, const std::string& var2, int var3, int var4, int var5, int var6, int var7, KahluaTable var8) {
      if (!var2 == "Vehicle") && !var2 == "ParkingStall")) {
    return nullptr;
      } else {
         var1 = this.sharedStrings.get(var1);
         var2 = this.sharedStrings.get(var2);
    VehicleZone var9 = std::make_shared<VehicleZone>(var1, var2, var3, var4, var5, var6, var7, var8);
         this.VehiclesZones.push_back(var9);
    int var10 = (int)Math.ceil((var9.x + var9.w) / 300.0F);
    int var11 = (int)Math.ceil((var9.y + var9.h) / 300.0F);

         for (int var12 = var9.y / 300; var12 < var11; var12++) {
            for (int var13 = var9.x / 300; var13 < var10; var13++) {
               if (var13 >= this.minX
                  && var13 <= this.maxX
                  && var12 >= this.minY
                  && var12 <= this.maxY
                  && this.Grid[var13 - this.minX][var12 - this.minY] != nullptr) {
                  this.Grid[var13 - this.minX][var12 - this.minY].vehicleZones.push_back(var9);
               }
            }
         }

    return var9;
      }
   }

    void checkVehiclesZones() {
    int var4 = 0;

      while (var4 < this.VehiclesZones.size()) {
    bool var1 = true;

         for (int var5 = 0; var5 < var4; var5++) {
    Zone var2 = (Zone)this.VehiclesZones.get(var4);
    Zone var3 = (Zone)this.VehiclesZones.get(var5);
            if (var2.getX() == var3.getX() && var2.getY() == var3.getY() && var2.h == var3.h && var2.w == var3.w) {
               var1 = false;
               DebugLog.log(
                  "checkVehiclesZones: ERROR! Zone '"
                     + var2.name
                     + "':'"
                     + var2.type
                     + "' ("
                     + var2.x
                     + ", "
                     + var2.y
                     + ") duplicate with Zone '"
                     + var3.name
                     + "':'"
                     + var3.type
                     + "' ("
                     + var3.x
                     + ", "
                     + var3.y
                     + ")"
               );
               break;
            }
         }

         if (var1) {
            var4++;
         } else {
            this.VehiclesZones.remove(var4);
         }
      }
   }

    Zone registerMannequinZone(const std::string& var1, const std::string& var2, int var3, int var4, int var5, int var6, int var7, KahluaTable var8) {
      if (!"Mannequin" == var2)) {
    return nullptr;
      } else {
         var1 = this.sharedStrings.get(var1);
         var2 = this.sharedStrings.get(var2);
    MannequinZone var9 = std::make_shared<MannequinZone>(var1, var2, var3, var4, var5, var6, var7, var8);
    int var10 = (int)Math.ceil((var9.x + var9.w) / 300.0F);
    int var11 = (int)Math.ceil((var9.y + var9.h) / 300.0F);

         for (int var12 = var9.y / 300; var12 < var11; var12++) {
            for (int var13 = var9.x / 300; var13 < var10; var13++) {
               if (var13 >= this.minX
                  && var13 <= this.maxX
                  && var12 >= this.minY
                  && var12 <= this.maxY
                  && this.Grid[var13 - this.minX][var12 - this.minY] != nullptr) {
                  this.Grid[var13 - this.minX][var12 - this.minY].mannequinZones.push_back(var9);
               }
            }
         }

    return var9;
      }
   }

    void registerRoomTone(const std::string& var1, const std::string& var2, int var3, int var4, int var5, int var6, int var7, KahluaTable var8) {
      if ("RoomTone" == var2)) {
    IsoMetaCell var9 = this.getCellData(var3 / 300, var4 / 300);
         if (var9 != nullptr) {
    RoomTone var10 = std::make_shared<RoomTone>();
            var10.x = var3;
            var10.y = var4;
            var10.z = var5;
            var10.enumValue = var8.getString("RoomTone");
            var10.entireBuilding = bool.TRUE == var8.rawget("EntireBuilding"));
            var9.roomTones.push_back(var10);
         }
      }
   }

    bool isZoneAbove(Zone var1, Zone var2, int var3, int var4, int var5) {
      if (var1 != nullptr && var1 != var2) {
    std::vector var6 = TL_ZoneList.get();
         var6.clear();
         this.getZonesAt(var3, var4, var5, var6);
         return var6.indexOf(var1) > var6.indexOf(var2);
      } else {
    return false;
      }
   }

    void save(ByteBuffer var1) {
      this.savePart(var1, 0, false);
      this.savePart(var1, 1, false);
   }

    void savePart(ByteBuffer var1, int var2, bool var3) {
      if (var2 == 0) {
         var1.put((byte)77);
         var1.put((byte)69);
         var1.put((byte)84);
         var1.put((byte)65);
         var1.putInt(195);
         var1.putInt(this.minX);
         var1.putInt(this.minY);
         var1.putInt(this.maxX);
         var1.putInt(this.maxY);

         for (int var16 = 0; var16 < this.Grid.length; var16++) {
            for (int var5 = 0; var5 < this.Grid[0].length; var5++) {
    IsoMetaCell var6 = this.Grid[var16][var5];
    int var7 = 0;
               if (var6.info != nullptr) {
                  var7 = var6.info.Rooms.values().size();
               }

               var1.putInt(var7);
               if (var6.info != nullptr) {
                  for (Entry var9 : var6.info.Rooms.entrySet()) {
    RoomDef var10 = (RoomDef)var9.getValue();
                     var1.putLong(var10.metaID);
    short var11 = 0;
                     if (var10.bExplored) {
                        var11 = (short)(var11 | 1);
                     }

                     if (var10.bLightsActive) {
                        var11 = (short)(var11 | 2);
                     }

                     if (var10.bDoneSpawn) {
                        var11 = (short)(var11 | 4);
                     }

                     if (var10.isRoofFixed()) {
                        var11 = (short)(var11 | 8);
                     }

                     var1.putShort(var11);
                  }
               }

               if (var6.info != nullptr) {
                  var1.putInt(var6.info.Buildings.size());
               } else {
                  var1.putInt(0);
               }

               if (var6.info != nullptr) {
                  for (BuildingDef var18 : var6.info.Buildings) {
                     var1.putLong(var18.metaID);
                     var1.put((byte)(var18.bAlarmed ? 1 : 0));
                     var1.putInt(var18.getKeyId());
                     var1.put((byte)(var18.seen ? 1 : 0));
                     var1.put((byte)(var18.isHasBeenVisited() ? 1 : 0));
                     var1.putInt(var18.lootRespawnHour);
                  }
               }
            }
         }
      } else {
         var1.putInt(SafeHouse.getSafehouseList().size());

         for (int var4 = 0; var4 < SafeHouse.getSafehouseList().size(); var4++) {
            ((SafeHouse)SafeHouse.getSafehouseList().get(var4)).save(var1);
         }

         var1.putInt(NonPvpZone.getAllZones().size());

         for (int var12 = 0; var12 < NonPvpZone.getAllZones().size(); var12++) {
            ((NonPvpZone)NonPvpZone.getAllZones().get(var12)).save(var1);
         }

         var1.putInt(Faction.getFactions().size());

         for (int var13 = 0; var13 < Faction.getFactions().size(); var13++) {
            ((Faction)Faction.getFactions().get(var13)).save(var1);
         }

         if (GameServer.bServer) {
    int var14 = var1.position();
            var1.putInt(0);
            StashSystem.save(var1);
            var1.putInt(var14, var1.position());
         } else if (!GameClient.bClient) {
            StashSystem.save(var1);
         }

         var1.putInt(RBBasic.getUniqueRDSSpawned().size());

         for (int var15 = 0; var15 < RBBasic.getUniqueRDSSpawned().size(); var15++) {
            GameWindow.WriteString(var1, (std::string)RBBasic.getUniqueRDSSpawned().get(var15));
         }
      }
   }

    void load() {
    File var1 = ZomboidFileSystem.instance.getFileInCurrentSave("map_meta.bin");

      try (
    FileInputStream var2 = std::make_shared<FileInputStream>(var1);
    BufferedInputStream var3 = std::make_shared<BufferedInputStream>(var2);
      ) {
         /* synchronized - TODO: add std::mutex */ (SliceY.SliceBufferLock) {
            SliceY.SliceBuffer.clear();
    int var5 = var3.read(SliceY.SliceBuffer.array());
            SliceY.SliceBuffer.limit(var5);
            this.load(SliceY.SliceBuffer);
         }
      } catch (FileNotFoundException var12) {
      } catch (Exception var13) {
         ExceptionLogger.logException(var13);
      }
   }

    void load(ByteBuffer var1) {
      var1.mark();
    uint8_t var3 = var1.get();
    uint8_t var4 = var1.get();
    uint8_t var5 = var1.get();
    uint8_t var6 = var1.get();
    int var2;
      if (var3 == 77 && var4 == 69 && var5 == 84 && var6 == 65) {
         var2 = var1.getInt();
      } else {
         var2 = 33;
         var1.reset();
      }

    int var7 = this.minX;
    int var8 = this.minY;
    int var9 = this.maxX;
    int var10 = this.maxY;
    int var11;
    int var12;
      if (var2 >= 194) {
         var7 = var1.getInt();
         var8 = var1.getInt();
         var9 = var1.getInt();
         var10 = var1.getInt();
         var11 = var9 - var7 + 1;
         var12 = var10 - var8 + 1;
      } else {
         var11 = var1.getInt();
         var12 = var1.getInt();
         if (var11 == 40 && var12 == 42 && this.width == 66 && this.height == 53 && this.getLotDirectories().contains("Muldraugh, KY")) {
            var7 = 10;
            var8 = 3;
         }

         var9 = var7 + var11 - 1;
         var10 = var8 + var12 - 1;
      }

      if (var11 != this.Grid.length || var12 != this.Grid[0].length) {
         DebugLog.log(
            "map_meta.bin world size (" + var11 + "x" + var12 + ") does not match the current map size (" + this.Grid.length + "x" + this.Grid[0].length + ")"
         );
      }

    int var13 = 0;
    int var14 = 0;

      for (int var15 = var7; var15 <= var9; var15++) {
         for (int var16 = var8; var16 <= var10; var16++) {
    IsoMetaCell var17 = this.getCellData(var15, var16);
    int var18 = var1.getInt();

            for (int var19 = 0; var19 < var18; var19++) {
    int var20 = var2 < 194 ? var1.getInt() : 0;
    long var21 = var2 >= 194 ? var1.getLong() : 0L;
    bool var23 = false;
    bool var24 = false;
    bool var25 = false;
    bool var26 = false;
               if (var2 >= 160) {
    short var27 = var1.getShort();
                  var23 = (var27 & 1) != 0;
                  var24 = (var27 & 2) != 0;
                  var25 = (var27 & 4) != 0;
                  var26 = (var27 & 8) != 0;
               } else {
                  var23 = var1.get() == 1;
                  if (var2 >= 34) {
                     var24 = var1.get() == 1;
                  } else {
                     var24 = Rand.Next(2) == 0;
                  }
               }

               if (var17 != nullptr && var17.info != nullptr) {
    RoomDef var59 = var2 < 194 ? (RoomDef)var17.info.Rooms.get(var20) : (RoomDef)var17.info.RoomByMetaID.get(var21);
                  if (var59 != nullptr) {
                     var59.setExplored(var23);
                     var59.bLightsActive = var24;
                     var59.bDoneSpawn = var25;
                     var59.setRoofFixed(var26);
                  } else if (var2 < 194) {
                     DebugLog.General.error("invalid room ID #" + var20 + " in cell " + var15 + "," + var16 + " while reading map_meta.bin");
                  } else {
                     DebugLog.General.error("invalid room metaID #" + var21 + " in cell " + var15 + "," + var16 + " while reading map_meta.bin");
                  }
               }
            }

    int var46 = var1.getInt();
            var13 += var46;

            for (int var50 = 0; var50 < var46; var50++) {
    long var52 = var2 >= 194 ? var1.getLong() : 0L;
    bool var54 = var1.get() == 1;
    int var56 = var2 >= 57 ? var1.getInt() : -1;
    bool var57 = var2 >= 74 ? var1.get() == 1 : false;
    bool var58 = var2 >= 107 ? var1.get() == 1 : false;
               if (var2 >= 111 && var2 < 121) {
                  var1.getInt();
               } else {
    bool var10000 = false;
               }

    int var28 = var2 >= 125 ? var1.getInt() : 0;
               if (var17 != nullptr && var17.info != nullptr) {
    BuildingDef var29 = nullptr;
                  if (var2 >= 194) {
                     var29 = (BuildingDef)var17.info.BuildingByMetaID.get(var52);
                  } else if (var50 < var17.info.Buildings.size()) {
                     var29 = (BuildingDef)var17.info.Buildings.get(var50);
                  }

                  if (var29 != nullptr) {
                     if (var54) {
                        var14++;
                     }

                     var29.bAlarmed = var54;
                     var29.setKeyId(var56);
                     if (var2 >= 74) {
                        var29.seen = var57;
                     }

                     var29.hasBeenVisited = var58;
                     var29.lootRespawnHour = var28;
                  } else if (var2 >= 194) {
                     DebugLog.General.error("invalid building metaID #" + var52 + " in cell " + var15 + "," + var16 + " while reading map_meta.bin");
                  }
               }
            }
         }
      }

      if (var2 <= 112) {
         this.Zones.clear();

         for (int var32 = 0; var32 < this.height; var32++) {
            for (int var34 = 0; var34 < this.width; var34++) {
    IsoMetaCell var37 = this.Grid[var34][var32];
               if (var37 != nullptr) {
                  for (int var40 = 0; var40 < 30; var40++) {
                     for (int var47 = 0; var47 < 30; var47++) {
                        var37.ChunkMap[var47 + var40 * 30].clearZones();
                     }
                  }
               }
            }
         }

         this.loadZone(var1, var2);
      }

      SafeHouse.clearSafehouseList();
    int var33 = var1.getInt();

      for (int var35 = 0; var35 < var33; var35++) {
         SafeHouse.load(var1, var2);
      }

      NonPvpZone.nonPvpZoneList.clear();
    int var36 = var1.getInt();

      for (int var38 = 0; var38 < var36; var38++) {
    NonPvpZone var41 = std::make_shared<NonPvpZone>();
         var41.load(var1, var2);
         NonPvpZone.getAllZones().push_back(var41);
      }

      Faction.factions = std::make_unique<std::vector>();
    int var39 = var1.getInt();

      for (int var42 = 0; var42 < var39; var42++) {
    Faction var48 = std::make_shared<Faction>();
         var48.load(var1, var2);
         Faction.getFactions().push_back(var48);
      }

      if (GameServer.bServer) {
    int var43 = var1.getInt();
         StashSystem.load(var1, var2);
      } else if (GameClient.bClient) {
    int var44 = var1.getInt();
         var1.position(var44);
      } else {
         StashSystem.load(var1, var2);
      }

    std::vector var45 = RBBasic.getUniqueRDSSpawned();
      var45.clear();
    int var49 = var1.getInt();

      for (int var51 = 0; var51 < var49; var51++) {
         var45.push_back(GameWindow.ReadString(var1));
      }
   }

    int getWidth() {
      return this.width;
   }

    int getHeight() {
      return this.height;
   }

    IsoMetaCell getCellData(int var1, int var2) {
      return var1 - this.minX >= 0 && var2 - this.minY >= 0 && var1 - this.minX < this.width && var2 - this.minY < this.height
         ? this.Grid[var1 - this.minX][var2 - this.minY]
         : nullptr;
   }

    IsoMetaCell getCellDataAbs(int var1, int var2) {
      return this.Grid[var1][var2];
   }

    IsoMetaCell getCurrentCellData() {
    int var1 = IsoWorld.instance.CurrentCell.ChunkMap[IsoPlayer.getPlayerIndex()].WorldX;
    int var2 = IsoWorld.instance.CurrentCell.ChunkMap[IsoPlayer.getPlayerIndex()].WorldY;
    float var3 = var1;
    float var4 = var2;
      var3 /= 30.0F;
      var4 /= 30.0F;
      if (var3 < 0.0F) {
         var3 = (int)var3 - 1;
      }

      if (var4 < 0.0F) {
         var4 = (int)var4 - 1;
      }

      var1 = (int)var3;
      var2 = (int)var4;
      return this.getCellData(var1, var2);
   }

    IsoMetaCell getMetaGridFromTile(int var1, int var2) {
    int var3 = var1 / 300;
    int var4 = var2 / 300;
      return this.getCellData(var3, var4);
   }

    IsoMetaChunk getCurrentChunkData() {
    int var1 = IsoWorld.instance.CurrentCell.ChunkMap[IsoPlayer.getPlayerIndex()].WorldX;
    int var2 = IsoWorld.instance.CurrentCell.ChunkMap[IsoPlayer.getPlayerIndex()].WorldY;
    float var3 = var1;
    float var4 = var2;
      var3 /= 30.0F;
      var4 /= 30.0F;
      if (var3 < 0.0F) {
         var3 = (int)var3 - 1;
      }

      if (var4 < 0.0F) {
         var4 = (int)var4 - 1;
      }

      var1 = (int)var3;
      var2 = (int)var4;
      return this.getCellData(var1, var2)
         .getChunk(
            IsoWorld.instance.CurrentCell.ChunkMap[IsoPlayer.getPlayerIndex()].WorldX - var1 * 30,
            IsoWorld.instance.CurrentCell.ChunkMap[IsoPlayer.getPlayerIndex()].WorldY - var2 * 30
         );
   }

    IsoMetaChunk getChunkData(int var1, int var2) {
    float var5 = var1;
    float var6 = var2;
      var5 /= 30.0F;
      var6 /= 30.0F;
      if (var5 < 0.0F) {
         var5 = (int)var5 - 1;
      }

      if (var6 < 0.0F) {
         var6 = (int)var6 - 1;
      }

    int var3 = (int)var5;
    int var4 = (int)var6;
    IsoMetaCell var7 = this.getCellData(var3, var4);
    return var7 = = nullptr ? nullptr : var7.getChunk(var1 - var3 * 30, var2 - var4 * 30);
   }

    IsoMetaChunk getChunkDataFromTile(int var1, int var2) {
    int var3 = var1 / 10;
    int var4 = var2 / 10;
      var3 -= this.minX * 30;
      var4 -= this.minY * 30;
    int var5 = var3 / 30;
    int var6 = var4 / 30;
      var3 += this.minX * 30;
      var4 += this.minY * 30;
      var5 += this.minX;
      var6 += this.minY;
    IsoMetaCell var7 = this.getCellData(var5, var6);
    return var7 = = nullptr ? nullptr : var7.getChunk(var3 - var5 * 30, var4 - var6 * 30);
   }

    bool isValidSquare(int var1, int var2) {
      if (var1 < this.minX * 300) {
    return false;
      } else if (var1 >= (this.maxX + 1) * 300) {
    return false;
      } else {
         return var2 < this.minY * 300 ? false : var2 < (this.maxY + 1) * 300;
      }
   }

    bool isValidChunk(int var1, int var2) {
      var1 *= 10;
      var2 *= 10;
      if (var1 < this.minX * 300) {
    return false;
      } else if (var1 >= (this.maxX + 1) * 300) {
    return false;
      } else if (var2 < this.minY * 300) {
    return false;
      } else {
         return var2 >= (this.maxY + 1) * 300 ? false : this.Grid[var1 / 300 - this.minX][var2 / 300 - this.minY].info != nullptr;
      }
   }

    void Create() {
      this.CreateStep1();
      this.CreateStep2();
   }

    void CreateStep1() {
      this.minX = 10000000;
      this.minY = 10000000;
      this.maxX = -10000000;
      this.maxY = -10000000;
      IsoLot.InfoHeaders.clear();
      IsoLot.InfoHeaderNames.clear();
      IsoLot.InfoFileNames.clear();
    long var1 = System.currentTimeMillis();
      DebugLog.log("IsoMetaGrid.Create: begin scanning directories");
    std::vector var4 = this.getLotDirectories();
      DebugLog.log("Looking in these map folders:");

    for (auto& var6 : var4)         var6 = ZomboidFileSystem.instance.getString("media/maps/" + var6 + "/");
         DebugLog.log("    " + std::make_shared<File>(var6).getAbsolutePath());
      }

      DebugLog.log("<End of map-folders list>");

    for (auto& var17 : var4)    File var3 = std::make_shared<File>(ZomboidFileSystem.instance.getString("media/maps/" + var17 + "/"));
         if (var3.isDirectory()) {
    std::unordered_map var7 = ChooseGameInfo.getMapDetails(var17);
            std::string[] var8 = var3.list();

            for (int var9 = 0; var9 < var8.length; var9++) {
               if (!IsoLot.InfoFileNames.containsKey(var8[var9])) {
                  if (var8[var9].endsWith(".lotheader")) {
                     std::string[] var10 = var8[var9].split("_");
                     var10[1] = var10[1].replace(".lotheader", "");
    int var11 = int.parseInt(var10[0].trim());
    int var12 = int.parseInt(var10[1].trim());
                     if (var11 < this.minX) {
                        this.minX = var11;
                     }

                     if (var12 < this.minY) {
                        this.minY = var12;
                     }

                     if (var11 > this.maxX) {
                        this.maxX = var11;
                     }

                     if (var12 > this.maxY) {
                        this.maxY = var12;
                     }

                     IsoLot.InfoFileNames.put(var8[var9], var3.getAbsolutePath() + File.separator + var8[var9]);
    LotHeader var13 = std::make_shared<LotHeader>();
                     var13.cellX = var11;
                     var13.cellY = var12;
                     var13.bFixed2x = var7.isFixed2x();
                     IsoLot.InfoHeaders.put(var8[var9], var13);
                     IsoLot.InfoHeaderNames.push_back(var8[var9]);
                  } else if (var8[var9].endsWith(".lotpack")) {
                     IsoLot.InfoFileNames.put(var8[var9], var3.getAbsolutePath() + File.separator + var8[var9]);
                  } else if (var8[var9].startsWith("chunkdata_")) {
                     IsoLot.InfoFileNames.put(var8[var9], var3.getAbsolutePath() + File.separator + var8[var9]);
                  }
               }
            }
         }
      }

      if (this.maxX >= this.minX && this.maxY >= this.minY) {
         this.Grid = new IsoMetaCell[this.maxX - this.minX + 1][this.maxY - this.minY + 1];
         this.width = this.maxX - this.minX + 1;
         this.height = this.maxY - this.minY + 1;
    long var15 = System.currentTimeMillis() - var1;
         DebugLog.log("IsoMetaGrid.Create: finished scanning directories in " + (float)var15 / 1000.0F + " seconds");
         DebugLog.log("IsoMetaGrid.Create: begin loading");
         this.createStartTime = System.currentTimeMillis();

         for (int var18 = 0; var18 < 8; var18++) {
    MetaGridLoaderThread var19 = std::make_shared<MetaGridLoaderThread>(this, this.minY + var18);
            var19.setDaemon(true);
            var19.setName("MetaGridLoaderThread" + var18);
            var19.start();
            this.threads[var18] = var19;
         }
      } else {
         throw IllegalStateException("Failed to find any .lotheader files");
      }
   }

    void CreateStep2() {
    bool var1 = true;

      while (var1) {
         var1 = false;

         for (int var2 = 0; var2 < 8; var2++) {
            if (this.threads[var2].isAlive()) {
               var1 = true;

               try {
                  Thread.sleep(100L);
               } catch (InterruptedException var5) {
               }
               break;
            }
         }
      }

      for (int var6 = 0; var6 < 8; var6++) {
         this.threads[var6].postLoad();
         this.threads[var6] = nullptr;
      }

      for (int var7 = 0; var7 < this.Buildings.size(); var7++) {
    BuildingDef var3 = this.Buildings.get(var7);
         if (!Core.GameMode == "LastStand") && var3.rooms.size() > 2) {
    uint8_t var4 = 11;
            if (SandboxOptions.instance.getElecShutModifier() > -1 && GameTime.instance.NightsSurvived < SandboxOptions.instance.getElecShutModifier()) {
               var4 = 9;
            }

            if (SandboxOptions.instance.Alarm.getValue() == 1) {
               var4 = -1;
            } else if (SandboxOptions.instance.Alarm.getValue() == 2) {
               var4 += 5;
            } else if (SandboxOptions.instance.Alarm.getValue() == 3) {
               var4 += 3;
            } else if (SandboxOptions.instance.Alarm.getValue() == 5) {
               var4 -= 3;
            } else if (SandboxOptions.instance.Alarm.getValue() == 6) {
               var4 -= 5;
            }

            if (var4 > -1) {
               var3.bAlarmed = Rand.Next(var4) == 0;
            }
         }
      }

    long var8 = System.currentTimeMillis() - this.createStartTime;
      DebugLog.log("IsoMetaGrid.Create: finished loading in " + (float)var8 / 1000.0F + " seconds");
   }

    void Dispose() {
      if (this.Grid != nullptr) {
         for (int var1 = 0; var1 < this.Grid.length; var1++) {
            IsoMetaCell[] var2 = this.Grid[var1];

            for (int var3 = 0; var3 < var2.length; var3++) {
    IsoMetaCell var4 = var2[var3];
               if (var4 != nullptr) {
                  var4.Dispose();
               }
            }

            Arrays.fill(var2, nullptr);
         }

         Arrays.fill(this.Grid, nullptr);
         this.Grid = nullptr;

         for (BuildingDef var7 : this.Buildings) {
            var7.Dispose();
         }

         this.Buildings.clear();
         this.VehiclesZones.clear();

         for (Zone var8 : this.Zones) {
            var8.Dispose();
         }

         this.Zones.clear();
         this.sharedStrings.clear();
      }
   }

    Vector2 getRandomIndoorCoord() {
    return nullptr;
   }

    RoomDef getRandomRoomBetweenRange(float var1, float var2, float var3, float var4) {
    void* var5 = nullptr;
    float var6 = 0.0F;
      roomChoices.clear();
    void* var7 = nullptr;

      for (int var8 = 0; var8 < IsoLot.InfoHeaderNames.size(); var8++) {
         var7 = (LotHeader)IsoLot.InfoHeaders.get(IsoLot.InfoHeaderNames.get(var8));
         if (!((LotHeader)var7).RoomList.empty()) {
            for (int var9 = 0; var9 < ((LotHeader)var7).RoomList.size(); var9++) {
               var5 = (RoomDef)((LotHeader)var7).RoomList.get(var9);
               var6 = IsoUtils.DistanceManhatten(var1, var2, ((RoomDef)var5).x, ((RoomDef)var5).y);
               if (var6 > var3 && var6 < var4) {
                  roomChoices.push_back((RoomDef)var5);
               }
            }
         }
      }

      return !roomChoices.empty() ? roomChoices.get(Rand.Next(roomChoices.size())) : nullptr;
   }

    RoomDef getRandomRoomNotInRange(float var1, float var2, int var3) {
    RoomDef var4 = nullptr;

      do {
    void* var5 = nullptr;

         do {
            var5 = (LotHeader)IsoLot.InfoHeaders.get(IsoLot.InfoHeaderNames.get(Rand.Next(IsoLot.InfoHeaderNames.size())));
         } while (((LotHeader)var5).RoomList.empty());

         var4 = (RoomDef)((LotHeader)var5).RoomList.get(Rand.Next(((LotHeader)var5).RoomList.size()));
      } while (var4 == nullptr || IsoUtils.DistanceManhatten(var1, var2, var4.x, var4.y) < var3);

    return var4;
   }

    void save() {
      try {
    File var1 = ZomboidFileSystem.instance.getFileInCurrentSave("map_meta.bin");

         try (
    FileOutputStream var2 = std::make_shared<FileOutputStream>(var1);
    BufferedOutputStream var3 = std::make_shared<BufferedOutputStream>(var2);
         ) {
            /* synchronized - TODO: add std::mutex */ (SliceY.SliceBufferLock) {
               SliceY.SliceBuffer.clear();
               this.save(SliceY.SliceBuffer);
               var3.write(SliceY.SliceBuffer.array(), 0, SliceY.SliceBuffer.position());
            }
         }

    File var18 = ZomboidFileSystem.instance.getFileInCurrentSave("map_zone.bin");

         try (
    FileOutputStream var19 = std::make_shared<FileOutputStream>(var18);
    BufferedOutputStream var20 = std::make_shared<BufferedOutputStream>(var19);
         ) {
            /* synchronized - TODO: add std::mutex */ (SliceY.SliceBufferLock) {
               SliceY.SliceBuffer.clear();
               this.saveZone(SliceY.SliceBuffer);
               var20.write(SliceY.SliceBuffer.array(), 0, SliceY.SliceBuffer.position());
            }
         }
      } catch (Exception var17) {
         ExceptionLogger.logException(var17);
      }
   }

    void loadZones() {
    File var1 = ZomboidFileSystem.instance.getFileInCurrentSave("map_zone.bin");

      try (
    FileInputStream var2 = std::make_shared<FileInputStream>(var1);
    BufferedInputStream var3 = std::make_shared<BufferedInputStream>(var2);
      ) {
         /* synchronized - TODO: add std::mutex */ (SliceY.SliceBufferLock) {
            SliceY.SliceBuffer.clear();
    int var5 = var3.read(SliceY.SliceBuffer.array());
            SliceY.SliceBuffer.limit(var5);
            this.loadZone(SliceY.SliceBuffer, -1);
         }
      } catch (FileNotFoundException var12) {
      } catch (Exception var13) {
         ExceptionLogger.logException(var13);
      }
   }

    void loadZone(ByteBuffer var1, int var2) {
      if (var2 == -1) {
    uint8_t var3 = var1.get();
    uint8_t var4 = var1.get();
    uint8_t var5 = var1.get();
    uint8_t var6 = var1.get();
         if (var3 != 90 || var4 != 79 || var5 != 78 || var6 != 69) {
            DebugLog.log("ERROR: expected 'ZONE' at start of map_zone.bin");
            return;
         }

         var2 = var1.getInt();
      }

    int var22 = this.Zones.size();
      if (!GameServer.bServer && var2 >= 34 || GameServer.bServer && var2 >= 36) {
         for (Zone var26 : this.Zones) {
            var26.Dispose();
         }

         this.Zones.clear();

         for (int var24 = 0; var24 < this.height; var24++) {
            for (int var27 = 0; var27 < this.width; var27++) {
    IsoMetaCell var29 = this.Grid[var27][var24];
               if (var29 != nullptr) {
                  for (int var7 = 0; var7 < 30; var7++) {
                     for (int var8 = 0; var8 < 30; var8++) {
                        var29.ChunkMap[var8 + var7 * 30].clearZones();
                     }
                  }
               }
            }
         }

         ZoneGeometryType[] var25 = ZoneGeometryType.values();
    TIntArrayList var28 = std::make_shared<TIntArrayList>();
         if (var2 >= 141) {
    int var31 = var1.getInt();
    std::unordered_map var33 = new std::unordered_map();

            for (int var35 = 0; var35 < var31; var35++) {
    std::string var37 = GameWindow.ReadStringUTF(var1);
               var33.put(var35, var37);
            }

    int var36 = var1.getInt();
            DebugLog.log("loading " + var36 + " zones from map_zone.bin");

            for (int var38 = 0; var38 < var36; var38++) {
    std::string var40 = (std::string)var33.get(int.valueOf(var1.getShort()));
    std::string var42 = (std::string)var33.get(int.valueOf(var1.getShort()));
    int var44 = var1.getInt();
    int var46 = var1.getInt();
    uint8_t var48 = var1.get();
    int var15 = var1.getInt();
    int var50 = var1.getInt();
    ZoneGeometryType var51 = ZoneGeometryType.INVALID;
               var28.clear();
    int var53 = 0;
               if (var2 >= 185) {
    uint8_t var19 = var1.get();
                  if (var19 < 0 || var19 >= var25.length) {
                     var19 = 0;
                  }

                  var51 = var25[var19];
                  if (var51 != ZoneGeometryType.INVALID) {
                     if (var2 >= 186 && var51 == ZoneGeometryType.Polyline) {
                        var53 = PZMath.clamp(var1.get(), 0, 255);
                     }

    short var20 = var1.getShort();

                     for (int var21 = 0; var21 < var20; var21++) {
                        var28.push_back(var1.getInt());
                     }
                  }
               }

    int var54 = var1.getInt();
    Zone var55 = this.registerZone(var40, var42, var44, var46, var48, var15, var50, var51, var51 == ZoneGeometryType.INVALID ? nullptr : var28, var53);
               var55.hourLastSeen = var54;
               var55.haveConstruction = var1.get() == 1;
               var55.lastActionTimestamp = var1.getInt();
               var55.setOriginalName((std::string)var33.get(int.valueOf(var1.getShort())));
               var55.id = var1.getDouble();
            }

    int var39 = var1.getInt();

            for (int var41 = 0; var41 < var39; var41++) {
    std::string var43 = GameWindow.ReadString(var1);
    std::vector var45 = new std::vector();
    int var47 = var1.getInt();

               for (int var49 = 0; var49 < var47; var49++) {
                  var45.push_back(var1.getDouble());
               }

               IsoWorld.instance.getSpawnedZombieZone().put(var43, var45);
            }

            return;
         }

    int var30 = var1.getInt();
         DebugLog.log("loading " + var30 + " zones from map_zone.bin");
         if (var2 <= 112 && var30 > var22 * 2) {
            DebugLog.log("ERROR: seems like too many zones in map_zone.bin");
            return;
         }

         for (int var32 = 0; var32 < var30; var32++) {
    std::string var34 = GameWindow.ReadString(var1);
    std::string var9 = GameWindow.ReadString(var1);
    int var10 = var1.getInt();
    int var11 = var1.getInt();
    int var12 = var1.getInt();
    int var13 = var1.getInt();
    int var14 = var1.getInt();
            if (var2 < 121) {
               var1.getInt();
            } else {
    bool var10000 = false;
            }

    int var16 = var2 < 68 ? var1.getShort() : var1.getInt();
    Zone var17 = this.registerZone(var34, var9, var10, var11, var12, var13, var14);
            var17.hourLastSeen = var16;
            if (var2 >= 35) {
    bool var18 = var1.get() == 1;
               var17.haveConstruction = var18;
            }

            if (var2 >= 41) {
               var17.lastActionTimestamp = var1.getInt();
            }

            if (var2 >= 98) {
               var17.setOriginalName(GameWindow.ReadString(var1));
            }

            if (var2 >= 110 && var2 < 121) {
    int var52 = var1.getInt();
            }

            var17.id = var1.getDouble();
         }
      }
   }

    void saveZone(ByteBuffer var1) {
      var1.put((byte)90);
      var1.put((byte)79);
      var1.put((byte)78);
      var1.put((byte)69);
      var1.putInt(195);
    std::unordered_set var2 = new std::unordered_set();

      for (int var3 = 0; var3 < this.Zones.size(); var3++) {
    Zone var4 = this.Zones.get(var3);
         var2.push_back(var4.getName());
         var2.push_back(var4.getOriginalName());
         var2.push_back(var4.getType());
      }

    std::vector var9 = new std::vector(var2);
    std::unordered_map var10 = new std::unordered_map();

      for (int var5 = 0; var5 < var9.size(); var5++) {
         var10.put((std::string)var9.get(var5), var5);
      }

      if (var9.size() > 32767) {
         throw IllegalStateException("IsoMetaGrid.saveZone() string table is too large");
      } else {
         var1.putInt(var9.size());

         for (int var11 = 0; var11 < var9.size(); var11++) {
            GameWindow.WriteString(var1, (std::string)var9.get(var11));
         }

         var1.putInt(this.Zones.size());

         for (int var12 = 0; var12 < this.Zones.size(); var12++) {
    Zone var6 = this.Zones.get(var12);
            var1.putShort(((int)var10.get(var6.getName())).shortValue());
            var1.putShort(((int)var10.get(var6.getType())).shortValue());
            var1.putInt(var6.x);
            var1.putInt(var6.y);
            var1.put((byte)var6.z);
            var1.putInt(var6.w);
            var1.putInt(var6.h);
            var1.put((byte)var6.geometryType.ordinal());
            if (!var6.isRectangle()) {
               if (var6.isPolyline()) {
                  var1.put((byte)var6.polylineWidth);
               }

               var1.putShort((short)var6.points.size());

               for (int var7 = 0; var7 < var6.points.size(); var7++) {
                  var1.putInt(var6.points.get(var7));
               }
            }

            var1.putInt(var6.hourLastSeen);
            var1.put((byte)(var6.haveConstruction ? 1 : 0));
            var1.putInt(var6.lastActionTimestamp);
            var1.putShort(((int)var10.get(var6.getOriginalName())).shortValue());
            var1.putDouble(var6.id);
         }

         var2.clear();
         var9.clear();
         var10.clear();
         var1.putInt(IsoWorld.instance.getSpawnedZombieZone().size());

         for (std::string var14 : IsoWorld.instance.getSpawnedZombieZone().keySet()) {
    std::vector var15 = (std::vector)IsoWorld.instance.getSpawnedZombieZone().get(var14);
            GameWindow.WriteString(var1, var14);
            var1.putInt(var15.size());

            for (int var8 = 0; var8 < var15.size(); var8++) {
               var1.putDouble((double)var15.get(var8));
            }
         }
      }
   }

    void getLotDirectories(const std::string& var1, std::vector<std::string> var2) {
      if (!var2.contains(var1)) {
    std::unordered_map var3 = ChooseGameInfo.getMapDetails(var1);
         if (var3 != nullptr) {
            var2.push_back(var1);

            for (std::string var5 : var3.getLotDirectories()) {
               this.getLotDirectories(var5, var2);
            }
         }
      }
   }

   public std::vector<std::string> getLotDirectories() {
      if (GameClient.bClient) {
         Core.GameMap = GameClient.GameMap;
      }

      if (GameServer.bServer) {
         Core.GameMap = GameServer.GameMap;
      }

      if (Core.GameMap == "DEFAULT")) {
    MapGroups var1 = std::make_shared<MapGroups>();
         var1.createGroups();
         if (var1.getNumberOfGroups() != 1) {
            throw RuntimeException("GameMap is DEFAULT but there are multiple worlds to choose from");
         }

         var1.setWorld(0);
      }

    std::vector var5 = new std::vector();
      if (Core.GameMap.contains(";")) {
         std::string[] var2 = Core.GameMap.split(";");

         for (int var3 = 0; var3 < var2.length; var3++) {
    std::string var4 = var2[var3].trim();
            if (!var4.empty() && !var5.contains(var4)) {
               var5.push_back(var4);
            }
         }
      } else {
         this.getLotDirectories(Core.GameMap, var5);
      }

    return var5;
   }

    static bool isPreferredZoneForSquare(const std::string& var0) {
      return s_PreferredZoneTypes.contains(var0);
   }

   static {
      s_PreferredZoneTypes.push_back("DeepForest");
      s_PreferredZoneTypes.push_back("Farm");
      s_PreferredZoneTypes.push_back("FarmLand");
      s_PreferredZoneTypes.push_back("Forest");
      s_PreferredZoneTypes.push_back("Vegitation");
      s_PreferredZoneTypes.push_back("Nav");
      s_PreferredZoneTypes.push_back("TownZone");
      s_PreferredZoneTypes.push_back("TrailerPark");
   }
}
} // namespace iso
} // namespace zombie
