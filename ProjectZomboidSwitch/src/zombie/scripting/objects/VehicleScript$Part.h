#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/scripting/objects/VehicleScript/Anim.h"
#include "zombie/scripting/objects/VehicleScript/Container.h"
#include "zombie/scripting/objects/VehicleScript/Door.h"
#include "zombie/scripting/objects/VehicleScript/Model.h"
#include "zombie/scripting/objects/VehicleScript/Window.h"
#include <algorithm>

namespace zombie {
namespace scripting {
namespace objects {


class VehicleScript {
public:
    std::string id = "Unknown";
    std::string parent;
   public std::vector<std::string> itemType;
    Container container;
    std::string area;
    std::string wheel;
   public std::unordered_map<std::string, KahluaTable> tables;
   public std::unordered_map<std::string, std::string> luaFunctions;
   public std::vector<Model> models;
    bool bSetAllModelsVisible = true;
    Door door;
    Window window;
   public std::vector<Anim> anims;
    std::string category;
    bool specificItem = true;
    bool mechanicRequireKey = false;
    bool repairMechanic = false;
    bool hasLightsRear = false;

    bool isMechanicRequireKey() {
      return this.mechanicRequireKey;
   }

    void setMechanicRequireKey(bool var1) {
      this.mechanicRequireKey = var1;
   }

    bool isRepairMechanic() {
      return this.repairMechanic;
   }

    void setRepairMechanic(bool var1) {
      this.repairMechanic = var1;
   }

   VehicleScript$Part makeCopy() {
      VehicleScript$Part var1 = new VehicleScript$Part();
      var1.id = this.id;
      var1.parent = this.parent;
      if (this.itemType != nullptr) {
         var1.itemType = std::make_unique<std::vector<>>();
         var1.itemType.addAll(this.itemType);
      }

      if (this.container != nullptr) {
         var1.container = this.container.makeCopy();
      }

      var1.area = this.area;
      var1.wheel = this.wheel;
      if (this.tables != nullptr) {
         var1.tables = std::make_unique<std::unordered_map<>>();

         for (Entry var3 : this.tables.entrySet()) {
    KahluaTable var4 = LuaManager.copyTable((KahluaTable)var3.getValue());
            var1.tables.put((std::string)var3.getKey(), var4);
         }
      }

      if (this.luaFunctions != nullptr) {
         var1.luaFunctions = std::make_unique<std::unordered_map<>>();
         var1.luaFunctions.putAll(this.luaFunctions);
      }

      if (this.models != nullptr) {
         var1.models = std::make_unique<std::vector<>>();

         for (int var5 = 0; var5 < this.models.size(); var5++) {
            var1.models.push_back(this.models.get(var5).makeCopy());
         }
      }

      var1.bSetAllModelsVisible = this.bSetAllModelsVisible;
      if (this.door != nullptr) {
         var1.door = this.door.makeCopy();
      }

      if (this.window != nullptr) {
         var1.window = this.window.makeCopy();
      }

      if (this.anims != nullptr) {
         var1.anims = std::make_unique<std::vector<>>();

         for (int var6 = 0; var6 < this.anims.size(); var6++) {
            var1.anims.push_back(this.anims.get(var6).makeCopy());
         }
      }

      var1.category = this.category;
      var1.specificItem = this.specificItem;
      var1.mechanicRequireKey = this.mechanicRequireKey;
      var1.repairMechanic = this.repairMechanic;
      var1.hasLightsRear = this.hasLightsRear;
    return var1;
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
