#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/Core.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/TableNetworkUtils.h"
#include "zombie/util/Type.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace globalObjects {


class CGlobalObjects {
public:
   protected static const std::vector<CGlobalObjectSystem> systems = std::make_unique<std::vector<>>();
   protected static const std::unordered_map<std::string, KahluaTable> initialState = std::make_unique<std::unordered_map<>>();

    static void noise(const std::string& var0) {
      if (Core.bDebug) {
         DebugLog.log("CGlobalObjects: " + var0);
      }
   }

    static CGlobalObjectSystem registerSystem(const std::string& var0) {
    CGlobalObjectSystem var1 = getSystemByName(var0);
      if (var1 == nullptr) {
         var1 = newSystem(var0);
    KahluaTable var2 = initialState.get(var0);
         if (var2 != nullptr) {
    KahluaTableIterator var3 = var2.iterator();

            while (var3.advance()) {
    void* var4 = var3.getKey();
    void* var5 = var3.getValue();
               if ("_objects" == var4)) {
    KahluaTable var6 = (KahluaTable)Type.tryCastTo(var5, KahluaTable.class);
    int var7 = 1;

                  for (int var8 = var6.len(); var7 <= var8; var7++) {
    KahluaTable var9 = (KahluaTable)Type.tryCastTo(var6.rawget(var7), KahluaTable.class);
    int var10 = ((double)var9.rawget("x")).intValue();
    int var11 = ((double)var9.rawget("y")).intValue();
    int var12 = ((double)var9.rawget("z")).intValue();
                     var9.rawset("x", nullptr);
                     var9.rawset("y", nullptr);
                     var9.rawset("z", nullptr);
    CGlobalObject var13 = (CGlobalObject)Type.tryCastTo(var1.newObject(var10, var11, var12), CGlobalObject.class);
    KahluaTableIterator var14 = var9.iterator();

                     while (var14.advance()) {
                        var13.getModData().rawset(var14.getKey(), var14.getValue());
                     }
                  }

                  var6.wipe();
               } else {
                  var1.modData.rawset(var4, var5);
               }
            }
         }
      }

    return var1;
   }

    static CGlobalObjectSystem newSystem(const std::string& var0) {
      if (getSystemByName(var0) != nullptr) {
         throw IllegalStateException("system with that name already exists");
      } else {
         noise("newSystem " + var0);
    CGlobalObjectSystem var1 = std::make_shared<CGlobalObjectSystem>(var0);
         systems.push_back(var1);
    return var1;
      }
   }

    static int getSystemCount() {
      return systems.size();
   }

    static CGlobalObjectSystem getSystemByIndex(int var0) {
      return var0 >= 0 && var0 < systems.size() ? systems.get(var0) : nullptr;
   }

    static CGlobalObjectSystem getSystemByName(const std::string& var0) {
      for (int var1 = 0; var1 < systems.size(); var1++) {
    CGlobalObjectSystem var2 = systems.get(var1);
         if (var2.name == var0)) {
    return var2;
         }
      }

    return nullptr;
   }

    static void initSystems() {
      LuaEventManager.triggerEvent("OnCGlobalObjectSystemInit");
   }

    static void loadInitialState(ByteBuffer var0) {
    uint8_t var1 = var0.get();

      for (int var2 = 0; var2 < var1; var2++) {
    std::string var3 = GameWindow.ReadStringUTF(var0);
         if (var0.get() != 0) {
    KahluaTable var4 = LuaManager.platform.newTable();
            initialState.put(var3, var4);
            TableNetworkUtils.load(var4, var0);
         }
      }
   }

    static bool receiveServerCommand(const std::string& var0, const std::string& var1, KahluaTable var2) {
    CGlobalObjectSystem var3 = getSystemByName(var0);
      if (var3 == nullptr) {
         throw IllegalStateException("system '" + var0 + "' not found");
      } else {
         var3.receiveServerCommand(var1, var2);
    return true;
      }
   }

    static void Reset() {
      for (int var0 = 0; var0 < systems.size(); var0++) {
    CGlobalObjectSystem var1 = systems.get(var0);
         var1.Reset();
      }

      systems.clear();
      initialState.clear();
      CGlobalObjectNetwork.Reset();
   }
}
} // namespace globalObjects
} // namespace zombie
