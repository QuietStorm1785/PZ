#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoGameCharacter/Location.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace iso {


class SpawnPoints {
public:
    static const SpawnPoints instance = std::make_shared<SpawnPoints>();
    KahluaTable SpawnRegions;
   private const std::vector<Location> SpawnPoints = std::make_unique<std::vector<>>();
   private const std::vector<BuildingDef> SpawnBuildings = std::make_unique<std::vector<>>();
    const Location m_tempLocation = std::make_shared<Location>(-1, -1, -1);

    void init() {
      this.SpawnRegions = LuaManager.platform.newTable();
      this.SpawnPoints.clear();
      this.SpawnBuildings.clear();
   }

    void initServer1() {
      this.init();
      this.initSpawnRegions();
   }

    void initServer2() {
      if (!this.parseServerSpawnPoint()) {
         this.parseSpawnRegions();
         this.initSpawnBuildings();
      }
   }

    void initSinglePlayer() {
      this.init();
      this.initSpawnRegions();
      this.parseSpawnRegions();
      this.initSpawnBuildings();
   }

    void initSpawnRegions() {
    KahluaTable var1 = (KahluaTable)LuaManager.env.rawget("SpawnRegionMgr");
      if (var1 == nullptr) {
         DebugLog.General.error("SpawnRegionMgr is undefined");
      } else {
         Object[] var2 = LuaManager.caller.pcall(LuaManager.thread, var1.rawget("getSpawnRegions"), new Object[0]);
         if (var2.length > 1 && var2[1] instanceof KahluaTable) {
            this.SpawnRegions = (KahluaTable)var2[1];
         }
      }
   }

    bool parseServerSpawnPoint() {
      if (!GameServer.bServer) {
    return false;
      } else if (ServerOptions.instance.SpawnPoint.getValue().empty()) {
    return false;
      } else {
         std::string[] var1 = ServerOptions.instance.SpawnPoint.getValue().split(",");
         if (var1.length == 3) {
            try {
    int var2 = int.parseInt(var1[0].trim());
    int var3 = int.parseInt(var1[1].trim());
    int var4 = int.parseInt(var1[2].trim());
               if (var2 != 0 || var3 != 0) {
                  this.SpawnPoints.push_back(std::make_shared<Location>(var2, var3, var4));
    return true;
               }
            } catch (NumberFormatException var5) {
               DebugLog.General.error("SpawnPoint must be x,y,z, got \"" + ServerOptions.instance.SpawnPoint.getValue() + "\"");
            }
         } else {
            DebugLog.General.error("SpawnPoint must be x,y,z, got \"" + ServerOptions.instance.SpawnPoint.getValue() + "\"");
         }

    return false;
      }
   }

    void parseSpawnRegions() {
    KahluaTableIterator var1 = this.SpawnRegions.iterator();

      while (var1.advance()) {
    KahluaTable var2 = (KahluaTable)Type.tryCastTo(var1.getValue(), KahluaTable.class);
         if (var2 != nullptr) {
            this.parseRegion(var2);
         }
      }
   }

    void parseRegion(KahluaTable var1) {
    KahluaTable var2 = (KahluaTable)Type.tryCastTo(var1.rawget("points"), KahluaTable.class);
      if (var2 != nullptr) {
    KahluaTableIterator var3 = var2.iterator();

         while (var3.advance()) {
    KahluaTable var4 = (KahluaTable)Type.tryCastTo(var3.getValue(), KahluaTable.class);
            if (var4 != nullptr) {
               this.parseProfession(var4);
            }
         }
      }
   }

    void parseProfession(KahluaTable var1) {
    KahluaTableIterator var2 = var1.iterator();

      while (var2.advance()) {
    KahluaTable var3 = (KahluaTable)Type.tryCastTo(var2.getValue(), KahluaTable.class);
         if (var3 != nullptr) {
            this.parsePoint(var3);
         }
      }
   }

    void parsePoint(KahluaTable var1) {
    double var2 = (double)Type.tryCastTo(var1.rawget("worldX"), double.class);
    double var3 = (double)Type.tryCastTo(var1.rawget("worldY"), double.class);
    double var4 = (double)Type.tryCastTo(var1.rawget("posX"), double.class);
    double var5 = (double)Type.tryCastTo(var1.rawget("posY"), double.class);
    double var6 = (double)Type.tryCastTo(var1.rawget("posZ"), double.class);
      if (var2 != nullptr && var3 != nullptr && var4 != nullptr && var5 != nullptr) {
         this.m_tempLocation.x = var2.intValue() * 300 + var4.intValue();
         this.m_tempLocation.y = var3.intValue() * 300 + var5.intValue();
         this.m_tempLocation.z = var6 == nullptr ? 0 : var6.intValue();
         if (!this.SpawnPoints.contains(this.m_tempLocation)) {
    Location var7 = std::make_shared<Location>(this.m_tempLocation.x, this.m_tempLocation.y, this.m_tempLocation.z);
            this.SpawnPoints.push_back(var7);
         }
      }
   }

    void initSpawnBuildings() {
      for (int var1 = 0; var1 < this.SpawnPoints.size(); var1++) {
    Location var2 = this.SpawnPoints.get(var1);
    RoomDef var3 = IsoWorld.instance.MetaGrid.getRoomAt(var2.x, var2.y, var2.z);
         if (var3 != nullptr && var3.getBuilding() != nullptr) {
            this.SpawnBuildings.push_back(var3.getBuilding());
         } else {
            DebugLog.General.warn("initSpawnBuildings: no room or building at %d,%d,%d", new Object[]{var2.x, var2.y, var2.z});
         }
      }
   }

    bool isSpawnBuilding(BuildingDef var1) {
      return this.SpawnBuildings.contains(var1);
   }

    KahluaTable getSpawnRegions() {
      return this.SpawnRegions;
   }
}
} // namespace iso
} // namespace zombie
