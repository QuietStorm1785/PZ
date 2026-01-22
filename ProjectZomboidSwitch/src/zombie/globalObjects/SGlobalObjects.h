#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/BoxedStaticValues.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/SliceY.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/TableNetworkUtils.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace globalObjects {


class SGlobalObjects {
public:
   protected static const std::vector<SGlobalObjectSystem> systems = std::make_unique<std::vector<>>();

    static void noise(const std::string& var0) {
      if (Core.bDebug) {
         DebugLog.log("SGlobalObjects: " + var0);
      }
   }

    static SGlobalObjectSystem registerSystem(const std::string& var0) {
    SGlobalObjectSystem var1 = getSystemByName(var0);
      if (var1 == nullptr) {
         var1 = newSystem(var0);
         var1.load();
      }

    return var1;
   }

    static SGlobalObjectSystem newSystem(const std::string& var0) {
      if (getSystemByName(var0) != nullptr) {
         throw IllegalStateException("system with that name already exists");
      } else {
         noise("newSystem " + var0);
    SGlobalObjectSystem var1 = std::make_shared<SGlobalObjectSystem>(var0);
         systems.push_back(var1);
    return var1;
      }
   }

    static int getSystemCount() {
      return systems.size();
   }

    static SGlobalObjectSystem getSystemByIndex(int var0) {
      return var0 >= 0 && var0 < systems.size() ? systems.get(var0) : nullptr;
   }

    static SGlobalObjectSystem getSystemByName(const std::string& var0) {
      for (int var1 = 0; var1 < systems.size(); var1++) {
    SGlobalObjectSystem var2 = systems.get(var1);
         if (var2.name == var0)) {
    return var2;
         }
      }

    return nullptr;
   }

    static void update() {
      for (int var0 = 0; var0 < systems.size(); var0++) {
    SGlobalObjectSystem var1 = systems.get(var0);
         var1.update();
      }
   }

    static void chunkLoaded(int var0, int var1) {
      for (int var2 = 0; var2 < systems.size(); var2++) {
    SGlobalObjectSystem var3 = systems.get(var2);
         var3.chunkLoaded(var0, var1);
      }
   }

    static void initSystems() {
      if (!GameClient.bClient) {
         LuaEventManager.triggerEvent("OnSGlobalObjectSystemInit");
         if (!GameServer.bServer) {
            try {
               /* synchronized - TODO: add std::mutex */ (SliceY.SliceBufferLock) {
                  SliceY.SliceBuffer.clear();
                  saveInitialStateForClient(SliceY.SliceBuffer);
                  SliceY.SliceBuffer.flip();
                  CGlobalObjects.loadInitialState(SliceY.SliceBuffer);
               }
            } catch (Throwable var3) {
               ExceptionLogger.logException(var3);
            }
         }
      }
   }

    static void saveInitialStateForClient(ByteBuffer var0) {
      var0.put((byte)systems.size());

      for (int var1 = 0; var1 < systems.size(); var1++) {
    SGlobalObjectSystem var2 = systems.get(var1);
         GameWindow.WriteStringUTF(var0, var2.name);
    KahluaTable var3 = var2.getInitialStateForClient();
         if (var3 == nullptr) {
            var3 = LuaManager.platform.newTable();
         }

    KahluaTable var4 = LuaManager.platform.newTable();
         var3.rawset("_objects", var4);

         for (int var5 = 0; var5 < var2.getObjectCount(); var5++) {
    GlobalObject var6 = var2.getObjectByIndex(var5);
    KahluaTable var7 = LuaManager.platform.newTable();
            var7.rawset("x", BoxedStaticValues.toDouble(var6.getX()));
            var7.rawset("y", BoxedStaticValues.toDouble(var6.getY()));
            var7.rawset("z", BoxedStaticValues.toDouble(var6.getZ()));

            for (std::string var9 : var2.objectSyncKeys) {
               var7.rawset(var9, var6.getModData().rawget(var9));
            }

            var4.rawset(var5 + 1, var7);
         }

         if (var3 != nullptr && !var3.empty()) {
            var0.put((byte)1);
            TableNetworkUtils.save(var3, var0);
         } else {
            var0.put((byte)0);
         }
      }
   }

    static bool receiveClientCommand(const std::string& var0, const std::string& var1, IsoPlayer var2, KahluaTable var3) {
      noise("receiveClientCommand " + var0 + " " + var1 + " OnlineID=" + var2.getOnlineID());
    SGlobalObjectSystem var4 = getSystemByName(var0);
      if (var4 == nullptr) {
         throw IllegalStateException("system '" + var0 + "' not found");
      } else {
         var4.receiveClientCommand(var1, var2, var3);
    return true;
      }
   }

    static void load() {
   }

    static void save() {
      for (int var0 = 0; var0 < systems.size(); var0++) {
    SGlobalObjectSystem var1 = systems.get(var0);
         var1.save();
      }
   }

    static void OnIsoObjectChangedItself(const std::string& var0, IsoObject var1) {
      if (!GameClient.bClient) {
    SGlobalObjectSystem var2 = getSystemByName(var0);
         if (var2 != nullptr) {
            var2.OnIsoObjectChangedItself(var1);
         }
      }
   }

    static void Reset() {
      for (int var0 = 0; var0 < systems.size(); var0++) {
    SGlobalObjectSystem var1 = systems.get(var0);
         var1.Reset();
      }

      systems.clear();
      GlobalObjectLookup.Reset();
   }
}
} // namespace globalObjects
} // namespace zombie
