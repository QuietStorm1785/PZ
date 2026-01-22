#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/core/Translator.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/scripting/ScriptManager.h"

namespace zombie {
namespace core {
namespace stash {


class Stash {
public:
    std::string name;
    std::string type;
    std::string item;
    std::string customName;
    int buildingX;
    int buildingY;
    std::string spawnTable;
   public std::vector<StashAnnotation> annotations;
    bool spawnOnlyOnZed;
    int minDayToSpawn = -1;
    int maxDayToSpawn = -1;
    int minTrapToSpawn = -1;
    int maxTrapToSpawn = -1;
    int zombies;
   public std::vector<StashContainer> containers;
    int barricades;

    public Stash(const std::string& var1) {
      this.name = var1;
   }

    void load(KahluaTableImpl var1) {
      this.type = var1.rawgetStr("type");
      this.item = var1.rawgetStr("item");
    StashBuilding var2 = std::make_shared<StashBuilding>(this.name, var1.rawgetInt("buildingX"), var1.rawgetInt("buildingY"));
      StashSystem.possibleStashes.push_back(var2);
      this.buildingX = var2.buildingX;
      this.buildingY = var2.buildingY;
      this.spawnTable = var1.rawgetStr("spawnTable");
      this.customName = Translator.getText(var1.rawgetStr("customName"));
      this.zombies = var1.rawgetInt("zombies");
      this.barricades = var1.rawgetInt("barricades");
      this.spawnOnlyOnZed = var1.rawgetBool("spawnOnlyOnZed");
    std::string var3 = var1.rawgetStr("daysToSpawn");
      if (var3 != nullptr) {
         std::string[] var4 = var3.split("-");
         if (var4.length == 2) {
            this.minDayToSpawn = int.parseInt(var4[0]);
            this.maxDayToSpawn = int.parseInt(var4[1]);
         } else {
            this.minDayToSpawn = int.parseInt(var4[0]);
         }
      }

    std::string var10 = var1.rawgetStr("traps");
      if (var10 != nullptr) {
         std::string[] var5 = var10.split("-");
         if (var5.length == 2) {
            this.minTrapToSpawn = int.parseInt(var5[0]);
            this.maxTrapToSpawn = int.parseInt(var5[1]);
         } else {
            this.minTrapToSpawn = int.parseInt(var5[0]);
            this.maxTrapToSpawn = this.minTrapToSpawn;
         }
      }

    KahluaTable var11 = (KahluaTable)var1.rawget("containers");
      if (var11 != nullptr) {
         this.containers = std::make_unique<std::vector<>>();
    KahluaTableIterator var6 = var11.iterator();

         while (var6.advance()) {
    KahluaTableImpl var7 = (KahluaTableImpl)var6.getValue();
    StashContainer var8 = std::make_shared<StashContainer>(var7.rawgetStr("room"), var7.rawgetStr("containerSprite"), var7.rawgetStr("containerType"));
            var8.contX = var7.rawgetInt("contX");
            var8.contY = var7.rawgetInt("contY");
            var8.contZ = var7.rawgetInt("contZ");
            var8.containerItem = var7.rawgetStr("containerItem");
            if (var8.containerItem != nullptr && ScriptManager.instance.getItem(var8.containerItem) == nullptr) {
               DebugLog.General.error("Stash containerItem \"%s\" doesn't exist.", new Object[]{var8.containerItem});
            }

            this.containers.push_back(var8);
         }
      }

      if ("Map" == this.type)) {
    KahluaTableImpl var12 = (KahluaTableImpl)var1.rawget("annotations");
         if (var12 != nullptr) {
            this.annotations = std::make_unique<std::vector<>>();
    KahluaTableIterator var13 = var12.iterator();

            while (var13.advance()) {
    KahluaTable var14 = (KahluaTable)var13.getValue();
    StashAnnotation var9 = std::make_shared<StashAnnotation>();
               var9.fromLua(var14);
               this.annotations.push_back(var9);
            }
         }
      }
   }

    std::string getName() {
      return this.name;
   }

    std::string getItem() {
      return this.item;
   }

    int getBuildingX() {
      return this.buildingX;
   }

    int getBuildingY() {
      return this.buildingY;
   }
}
} // namespace stash
} // namespace core
} // namespace zombie
