#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/SurvivorDesc.h"
#include "zombie/core/Rand.h"
#include "zombie/core/opengl/RenderSettings.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/ItemType.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoLightSource.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LotHeader.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoWindow.h"
#include <algorithm>
#include <iterator>

namespace zombie {
namespace iso {
namespace areas {


class IsoBuilding : public IsoArea {
public:
   zombie::core::Rect bounds;
   public const Vector<IsoRoomExit> Exits = std::make_unique<Vector<>>();
    bool IsResidence = true;
   public const std::vector<ItemContainer> container = std::make_unique<std::vector<>>();
   public const Vector<IsoRoom> Rooms = std::make_unique<Vector<>>();
   public const Vector<IsoWindow> Windows = std::make_unique<Vector<>>();
    int ID = 0;
    static int IDMax = 0;
    int safety = 0;
    int transparentWalls = 0;
    bool isToxic = false;
    static float PoorBuildingScore = 10.0F;
    static float GoodBuildingScore = 100.0F;
    int scoreUpdate = -1;
    BuildingDef def;
    bool bSeenInside = false;
   public std::vector<IsoLightSource> lights = std::make_unique<std::vector<>>();
   static std::vector<IsoRoom> tempo = std::make_unique<std::vector<>>();
   static std::vector<ItemContainer> tempContainer = std::make_unique<std::vector<>>();
   static std::vector<std::string> RandomContainerChoices = std::make_unique<std::vector<>>();
   static std::vector<IsoWindow> windowchoices = std::make_unique<std::vector<>>();

    int getRoomsNumber() {
      return this.Rooms.size();
   }

    public IsoBuilding() {
      this.ID = IDMax++;
      this.scoreUpdate = -120 + Rand.Next(120);
   }

    int getID() {
      return this.ID;
   }

    void TriggerAlarm() {
   }

    public IsoBuilding(IsoCell var1) {
      this.ID = IDMax++;
      this.scoreUpdate = -120 + Rand.Next(120);
   }

    bool ContainsAllItems(std::stack<std::string> var1) {
    return false;
   }

    float ScoreBuildingPersonSpecific(SurvivorDesc var1, bool var2) {
    float var3 = 0.0F;
      var3 += this.Rooms.size() * 5;
      var3 += this.Exits.size() * 15;
      var3 -= this.transparentWalls * 10;

      for (int var4 = 0; var4 < this.container.size(); var4++) {
    ItemContainer var5 = this.container.get(var4);
         var3 += var5.Items.size() * 3;
      }

      if (!IsoWorld.instance.CurrentCell.getBuildingScores().containsKey(this.ID)) {
    BuildingScore var12 = std::make_shared<BuildingScore>(this);
         var12.building = this;
         IsoWorld.instance.CurrentCell.getBuildingScores().put(this.ID, var12);
         this.ScoreBuildingGeneral(var12);
      }

    BuildingScore var13 = (BuildingScore)IsoWorld.instance.CurrentCell.getBuildingScores().get(this.ID);
      var3 += (var13.defense + var13.food + var13.size + var13.weapons + var13.wood) * 10.0F;
    int var14 = -10000;
    int var6 = -10000;
      if (!this.Exits.empty()) {
    IsoRoomExit var7 = this.Exits.get(0);
         var14 = var7.x;
         var6 = var7.y;
      }

    float var15 = IsoUtils.DistanceManhatten(var1.getInstance().getX(), var1.getInstance().getY(), var14, var6);
      if (var15 > 0.0F) {
         if (var2) {
            var3 *= var15 * 0.5F;
         } else {
            var3 /= var15 * 0.5F;
         }
      }

    return var3;
   }

    BuildingDef getDef() {
      return this.def;
   }

    void update() {
      if (!this.Exits.empty()) {
    int var1 = 0;
    int var2 = 0;

         for (int var3 = 0; var3 < this.Rooms.size(); var3++) {
    IsoRoom var4 = this.Rooms.get(var3);
            if (var4.layer == 0) {
               for (int var5 = 0; var5 < var4.TileList.size(); var5++) {
                  var2++;
    IsoGridSquare var6 = (IsoGridSquare)var4.TileList.get(var5);
               }
            }
         }

         if (var2 == 0) {
            var2++;
         }

         var1 = (int)((float)var1 / var2);
         this.scoreUpdate--;
         if (this.scoreUpdate <= 0) {
            this.scoreUpdate += 120;
    BuildingScore var8 = nullptr;
            if (IsoWorld.instance.CurrentCell.getBuildingScores().containsKey(this.ID)) {
               var8 = (BuildingScore)IsoWorld.instance.CurrentCell.getBuildingScores().get(this.ID);
            } else {
               var8 = std::make_shared<BuildingScore>(this);
               var8.building = this;
            }

            var8 = this.ScoreBuildingGeneral(var8);
            var8.defense += var1 * 10;
            this.safety = var1;
            IsoWorld.instance.CurrentCell.getBuildingScores().put(this.ID, var8);
         }
      }
   }

    void AddRoom(IsoRoom var1) {
      this.Rooms.push_back(var1);
      if (this.bounds == nullptr) {
         this.bounds = (Rectangle)var1.bounds.clone();
      }

      if (var1 != nullptr && var1.bounds != nullptr) {
         this.bounds.push_back(var1.bounds);
      }
   }

    void CalculateExits() {
      for (IsoRoom var2 : this.Rooms) {
         for (IsoRoomExit var4 : var2.Exits) {
            if (var4.To.From == nullptr && var2.layer == 0) {
               this.Exits.push_back(var4);
            }
         }
      }
   }

    void CalculateWindows() {
      for (IsoRoom var2 : this.Rooms) {
         for (IsoGridSquare var4 : var2.TileList) {
    IsoGridSquare var5 = var4.getCell().getGridSquare(var4.getX(), var4.getY() + 1, var4.getZ());
    IsoGridSquare var6 = var4.getCell().getGridSquare(var4.getX() + 1, var4.getY(), var4.getZ());
            if (var4.getProperties().Is(IsoFlagType.collideN) && var4.getProperties().Is(IsoFlagType.transparentN)) {
               var2.transparentWalls++;
               this.transparentWalls++;
            }

            if (var4.getProperties().Is(IsoFlagType.collideW) && var4.getProperties().Is(IsoFlagType.transparentW)) {
               var2.transparentWalls++;
               this.transparentWalls++;
            }

            if (var5 != nullptr) {
    bool var7 = var5.getRoom() != nullptr;
               if (var5.getRoom() != nullptr && var5.getRoom().building != var2.building) {
                  var7 = false;
               }

               if (var5.getProperties().Is(IsoFlagType.collideN) && var5.getProperties().Is(IsoFlagType.transparentN) && !var7) {
                  var2.transparentWalls++;
                  this.transparentWalls++;
               }
            }

            if (var6 != nullptr) {
    bool var9 = var6.getRoom() != nullptr;
               if (var6.getRoom() != nullptr && var6.getRoom().building != var2.building) {
                  var9 = false;
               }

               if (var6.getProperties().Is(IsoFlagType.collideW) && var6.getProperties().Is(IsoFlagType.transparentW) && !var9) {
                  var2.transparentWalls++;
                  this.transparentWalls++;
               }
            }

            for (int var10 = 0; var10 < var4.getSpecialObjects().size(); var10++) {
    IsoObject var8 = (IsoObject)var4.getSpecialObjects().get(var10);
               if (dynamic_cast<IsoWindow*>(var8) != nullptr) {
                  this.Windows.push_back((IsoWindow)var8);
               }
            }

            if (var5 != nullptr) {
               for (int var11 = 0; var11 < var5.getSpecialObjects().size(); var11++) {
    IsoObject var13 = (IsoObject)var5.getSpecialObjects().get(var11);
                  if (dynamic_cast<IsoWindow*>(var13) != nullptr) {
                     this.Windows.push_back((IsoWindow)var13);
                  }
               }
            }

            if (var6 != nullptr) {
               for (int var12 = 0; var12 < var6.getSpecialObjects().size(); var12++) {
    IsoObject var14 = (IsoObject)var6.getSpecialObjects().get(var12);
                  if (dynamic_cast<IsoWindow*>(var14) != nullptr) {
                     this.Windows.push_back((IsoWindow)var14);
                  }
               }
            }
         }
      }
   }

    void FillContainers() {
    bool var1 = false;

      for (IsoRoom var3 : this.Rooms) {
         if (var3.RoomDef != nullptr && var3.RoomDef.contains("tutorial")) {
            var1 = true;
         }

         if (!var3.TileList.empty()) {
    IsoGridSquare var4 = (IsoGridSquare)var3.TileList.get(0);
            if (var4.getX() < 74 && var4.getY() < 32) {
               var1 = true;
            }
         }

         if (var3.RoomDef.contains("shop")) {
            this.IsResidence = false;
         }

         for (IsoGridSquare var5 : var3.TileList) {
            for (int var6 = 0; var6 < var5.getObjects().size(); var6++) {
    IsoObject var7 = (IsoObject)var5.getObjects().get(var6);
               if (var7.hasWater()) {
                  var3.getWaterSources().push_back(var7);
               }

               if (var7.container != nullptr) {
                  this.container.push_back(var7.container);
                  var3.Containers.push_back(var7.container);
               }
            }

            if (var5.getProperties().Is(IsoFlagType.bed)) {
               var3.Beds.push_back(var5);
            }
         }
      }
   }

    ItemContainer getContainerWith(ItemType var1) {
      for (IsoRoom var3 : this.Rooms) {
         for (ItemContainer var5 : var3.Containers) {
            if (var5.HasType(var1)) {
    return var5;
            }
         }
      }

    return nullptr;
   }

    IsoRoom getRandomRoom() {
      return this.Rooms.size() == 0 ? nullptr : this.Rooms.get(Rand.Next(this.Rooms.size()));
   }

    BuildingScore ScoreBuildingGeneral(BuildingScore var1) {
      var1.food = 0.0F;
      var1.defense = 0.0F;
      var1.weapons = 0.0F;
      var1.wood = 0.0F;
      var1.building = this;
      var1.size = 0;
      var1.defense = var1.defense + (this.Exits.size() - 1) * 140;
      var1.defense = var1.defense - this.transparentWalls * 40;
      var1.size = this.Rooms.size() * 10;
      var1.size = var1.size + this.container.size() * 10;
    return var1;
   }

    IsoGridSquare getFreeTile() {
    IsoGridSquare var1 = nullptr;

      do {
    IsoRoom var2 = this.Rooms.get(Rand.Next(this.Rooms.size()));
         var1 = var2.getFreeTile();
      } while (var1 == nullptr);

    return var1;
   }

    bool hasWater() {
    Iterator var1 = this.Rooms.iterator();

      while (var1 != nullptr && var1.hasNext()) {
    IsoRoom var2 = (IsoRoom)var1.next();
         if (!var2.WaterSources.empty()) {
    IsoObject var3 = nullptr;
    int var4 = 0;

            while (true) {
               if (var4 < var2.WaterSources.size()) {
                  if (!((IsoObject)var2.WaterSources.get(var4)).hasWater()) {
                     var4++;
                     continue;
                  }

                  var3 = (IsoObject)var2.WaterSources.get(var4);
               }

               if (var3 != nullptr) {
    return true;
               }
               break;
            }
         }
      }

    return false;
   }

    void CreateFrom(BuildingDef var1, LotHeader var2) {
      for (int var3 = 0; var3 < var1.rooms.size(); var3++) {
    IsoRoom var4 = var2.getRoom(((RoomDef)var1.rooms.get(var3)).ID);
         var4.building = this;
         this.Rooms.push_back(var4);
      }
   }

    void setAllExplored(bool var1) {
      this.def.bAlarmed = false;

      for (int var2 = 0; var2 < this.Rooms.size(); var2++) {
    IsoRoom var3 = this.Rooms.get(var2);
         var3.def.setExplored(var1);

         for (int var4 = var3.def.getX(); var4 <= var3.def.getX2(); var4++) {
            for (int var5 = var3.def.getY(); var5 <= var3.def.getY2(); var5++) {
    IsoGridSquare var6 = IsoWorld.instance.CurrentCell.getGridSquare(var4, var5, var3.def.level);
               if (var6 != nullptr) {
                  var6.setHourSeenToCurrent();
               }
            }
         }
      }
   }

    bool isAllExplored() {
      for (int var1 = 0; var1 < this.Rooms.size(); var1++) {
    IsoRoom var2 = this.Rooms.get(var1);
         if (!var2.def.bExplored) {
    return false;
         }
      }

    return true;
   }

    void addWindow(IsoWindow var1, bool var2, IsoGridSquare var3, IsoBuilding var4) {
      this.Windows.push_back(var1);
    IsoGridSquare var5 = nullptr;
      if (var2) {
         var5 = var1.square;
      } else {
         var5 = var3;
      }

      if (var5 != nullptr) {
         if (var5.getRoom() == nullptr) {
    float var6 = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.7F;
    float var7 = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.7F;
    float var8 = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.7F;
    uint8_t var9 = 7;
    IsoLightSource var10 = std::make_shared<IsoLightSource>(var5.getX(), var5.getY(), var5.getZ(), var6, var7, var8, var9, var4);
            this.lights.push_back(var10);
            IsoWorld.instance.CurrentCell.getLamppostPositions().push_back(var10);
         }
      }
   }

    void addWindow(IsoWindow var1, bool var2) {
      this.addWindow(var1, var2, var1.square, nullptr);
   }

    void addDoor(IsoDoor var1, bool var2, IsoGridSquare var3, IsoBuilding var4) {
    IsoGridSquare var5 = nullptr;
      if (var2) {
         var5 = var1.square;
      } else {
         var5 = var3;
      }

      if (var5 != nullptr) {
         if (var5.getRoom() == nullptr) {
    float var6 = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.7F;
    float var7 = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.7F;
    float var8 = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.7F;
    uint8_t var9 = 7;
    IsoLightSource var10 = std::make_shared<IsoLightSource>(var5.getX(), var5.getY(), var5.getZ(), var6, var7, var8, var9, var4);
            this.lights.push_back(var10);
            IsoWorld.instance.CurrentCell.getLamppostPositions().push_back(var10);
         }
      }
   }

    void addDoor(IsoDoor var1, bool var2) {
      this.addDoor(var1, var2, var1.square, nullptr);
   }

    bool isResidential() {
      return this.containsRoom("bedroom");
   }

    bool containsRoom(const std::string& var1) {
      for (int var2 = 0; var2 < this.Rooms.size(); var2++) {
         if (var1 == this.Rooms.get(var2).getName())) {
    return true;
         }
      }

    return false;
   }

    IsoRoom getRandomRoom(const std::string& var1) {
      tempo.clear();

      for (int var2 = 0; var2 < this.Rooms.size(); var2++) {
         if (var1 == this.Rooms.get(var2).getName())) {
            tempo.push_back(this.Rooms.get(var2));
         }
      }

      return tempo.empty() ? nullptr : tempo.get(Rand.Next(tempo.size()));
   }

    ItemContainer getRandomContainer(const std::string& var1) {
      RandomContainerChoices.clear();
      std::string[] var2 = nullptr;
      if (var1 != nullptr) {
         var2 = var1.split(",");
      }

      if (var2 != nullptr) {
         for (int var3 = 0; var3 < var2.length; var3++) {
            RandomContainerChoices.push_back(var2[var3]);
         }
      }

      tempContainer.clear();

      for (int var7 = 0; var7 < this.Rooms.size(); var7++) {
    IsoRoom var4 = this.Rooms.get(var7);

         for (int var5 = 0; var5 < var4.Containers.size(); var5++) {
    ItemContainer var6 = (ItemContainer)var4.Containers.get(var5);
            if (var1 == nullptr || RandomContainerChoices.contains(var6.getType())) {
               tempContainer.push_back(var6);
            }
         }
      }

      return tempContainer.empty() ? nullptr : tempContainer.get(Rand.Next(tempContainer.size()));
   }

    IsoWindow getRandomFirstFloorWindow() {
      windowchoices.clear();
      windowchoices.addAll(this.Windows);

      for (int var1 = 0; var1 < windowchoices.size(); var1++) {
         if (windowchoices.get(var1).getZ() > 0.0F) {
            windowchoices.remove(var1);
         }
      }

      return !windowchoices.empty() ? windowchoices.get(Rand.Next(windowchoices.size())) : nullptr;
   }

    bool isToxic() {
      return this.isToxic;
   }

    void setToxic(bool var1) {
      this.isToxic = var1;
   }

    void forceAwake() {
      for (int var1 = this.def.getX(); var1 <= this.def.getX2(); var1++) {
         for (int var2 = this.def.getY(); var2 <= this.def.getY2(); var2++) {
            for (int var3 = 0; var3 <= 4; var3++) {
    IsoGridSquare var4 = IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, var3);
               if (var4 != nullptr) {
                  for (int var5 = 0; var5 < var4.getMovingObjects().size(); var5++) {
                     if (var4.getMovingObjects().get(var5) instanceof IsoGameCharacter) {
                        ((IsoGameCharacter)var4.getMovingObjects().get(var5)).forceAwake();
                     }
                  }
               }
            }
         }
      }
   }
}
} // namespace areas
} // namespace iso
} // namespace zombie
