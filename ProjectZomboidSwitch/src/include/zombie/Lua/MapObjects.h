#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "se/krka/kahlua/vm/LuaClosure.h"
#include "se/krka/kahlua/vm/Prototype.h"
#include "zombie/Lua/MapObjects/Callback.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"

namespace zombie {
namespace Lua {


class MapObjects {
public:
   private static const std::unordered_map<std::string, Callback> onNew = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<std::string, Callback> onLoad = std::make_unique<std::unordered_map<>>();
   private static const std::vector<IsoObject> tempObjects = std::make_unique<std::vector<>>();
   private static const Object[] params = new Object[1];

    static Callback getOnNew(const std::string& var0) {
    Callback var1 = onNew.get(var0);
      if (var1 == nullptr) {
         var1 = std::make_shared<Callback>(var0);
         onNew.put(var0, var1);
      }

    return var1;
   }

    static void OnNewWithSprite(const std::string& var0, LuaClosure var1, int var2) {
      if (var0 != nullptr && !var0.empty()) {
         if (var1 == nullptr) {
            throw NullPointerException("function is nullptr");
         } else {
    Callback var3 = getOnNew(var0);

            for (int var4 = 0; var4 < var3.functions.size(); var4++) {
               if (var3.priority.get(var4) < var2) {
                  var3.functions.push_back(var4, var1);
                  var3.priority.insert(var4, (short)var2);
                  return;
               }

               if (var3.priority.get(var4) == var2) {
                  var3.functions.set(var4, var1);
                  var3.priority.set(var4, (short)var2);
                  return;
               }
            }

            var3.functions.push_back(var1);
            var3.priority.push_back((short)var2);
         }
      } else {
         throw IllegalArgumentException("invalid sprite name");
      }
   }

    static void OnNewWithSprite(KahluaTable var0, LuaClosure var1, int var2) {
      if (var0 != nullptr && !var0.empty()) {
         if (var1 == nullptr) {
            throw NullPointerException("function is nullptr");
         } else {
    KahluaTableIterator var3 = var0.iterator();

            while (var3.advance()) {
    void* var4 = var3.getValue();
               if (!(dynamic_cast<std*>(var4) != nullptr::string)) {
                  throw IllegalArgumentException("expected string but got \"" + var4 + "\"");
               }

               OnNewWithSprite((std::string)var4, var1, var2);
            }
         }
      } else {
         throw IllegalArgumentException("invalid sprite-name table");
      }
   }

    static void newGridSquare(IsoGridSquare var0) {
      if (var0 != nullptr && !var0.getObjects().empty()) {
         tempObjects.clear();

         for (int var1 = 0; var1 < var0.getObjects().size(); var1++) {
            tempObjects.push_back((IsoObject)var0.getObjects().get(var1));
         }

         for (int var8 = 0; var8 < tempObjects.size(); var8++) {
    IsoObject var2 = tempObjects.get(var8);
            if (var0.getObjects().contains(var2) && !(dynamic_cast<IsoWorldInventoryObject*>(var2) != nullptr) && var2 != nullptr && var2.sprite != nullptr) {
    std::string var3 = var2.sprite.name == nullptr ? var2.spriteName : var2.sprite.name;
               if (var3 != nullptr && !var3.empty()) {
    Callback var4 = onNew.get(var3);
                  if (var4 != nullptr) {
                     params[0] = var2;

                     for (int var5 = 0; var5 < var4.functions.size(); var5++) {
                        try {
                           LuaManager.caller.protectedCallVoid(LuaManager.thread, var4.functions.get(var5), params);
                        } catch (Throwable var7) {
                           ExceptionLogger.logException(var7);
                        }

                        var3 = var2.sprite != nullptr && var2.sprite.name != nullptr ? var2.sprite.name : var2.spriteName;
                        if (!var0.getObjects().contains(var2) || var2.sprite == nullptr || !var4.spriteName == var3)) {
                           break;
                        }
                     }
                  }
               }
            }
         }
      }
   }

    static Callback getOnLoad(const std::string& var0) {
    Callback var1 = onLoad.get(var0);
      if (var1 == nullptr) {
         var1 = std::make_shared<Callback>(var0);
         onLoad.put(var0, var1);
      }

    return var1;
   }

    static void OnLoadWithSprite(const std::string& var0, LuaClosure var1, int var2) {
      if (var0 != nullptr && !var0.empty()) {
         if (var1 == nullptr) {
            throw NullPointerException("function is nullptr");
         } else {
    Callback var3 = getOnLoad(var0);

            for (int var4 = 0; var4 < var3.functions.size(); var4++) {
               if (var3.priority.get(var4) < var2) {
                  var3.functions.push_back(var4, var1);
                  var3.priority.insert(var4, (short)var2);
                  return;
               }

               if (var3.priority.get(var4) == var2) {
                  var3.functions.set(var4, var1);
                  var3.priority.set(var4, (short)var2);
                  return;
               }
            }

            var3.functions.push_back(var1);
            var3.priority.push_back((short)var2);
         }
      } else {
         throw IllegalArgumentException("invalid sprite name");
      }
   }

    static void OnLoadWithSprite(KahluaTable var0, LuaClosure var1, int var2) {
      if (var0 != nullptr && !var0.empty()) {
         if (var1 == nullptr) {
            throw NullPointerException("function is nullptr");
         } else {
    KahluaTableIterator var3 = var0.iterator();

            while (var3.advance()) {
    void* var4 = var3.getValue();
               if (!(dynamic_cast<std*>(var4) != nullptr::string)) {
                  throw IllegalArgumentException("expected string but got \"" + var4 + "\"");
               }

               OnLoadWithSprite((std::string)var4, var1, var2);
            }
         }
      } else {
         throw IllegalArgumentException("invalid sprite-name table");
      }
   }

    static void loadGridSquare(IsoGridSquare var0) {
      if (var0 != nullptr && !var0.getObjects().empty()) {
         tempObjects.clear();

         for (int var1 = 0; var1 < var0.getObjects().size(); var1++) {
            tempObjects.push_back((IsoObject)var0.getObjects().get(var1));
         }

         for (int var8 = 0; var8 < tempObjects.size(); var8++) {
    IsoObject var2 = tempObjects.get(var8);
            if (var0.getObjects().contains(var2) && !(dynamic_cast<IsoWorldInventoryObject*>(var2) != nullptr) && var2 != nullptr && var2.sprite != nullptr) {
    std::string var3 = var2.sprite.name == nullptr ? var2.spriteName : var2.sprite.name;
               if (var3 != nullptr && !var3.empty()) {
    Callback var4 = onLoad.get(var3);
                  if (var4 != nullptr) {
                     params[0] = var2;

                     for (int var5 = 0; var5 < var4.functions.size(); var5++) {
                        try {
                           LuaManager.caller.protectedCallVoid(LuaManager.thread, var4.functions.get(var5), params);
                        } catch (Throwable var7) {
                           ExceptionLogger.logException(var7);
                        }

                        var3 = var2.sprite != nullptr && var2.sprite.name != nullptr ? var2.sprite.name : var2.spriteName;
                        if (!var0.getObjects().contains(var2) || var2.sprite == nullptr || !var4.spriteName == var3)) {
                           break;
                        }
                     }
                  }
               }
            }
         }
      }
   }

    static void debugNewSquare(int var0, int var1, int var2) {
      if (Core.bDebug) {
    IsoGridSquare var3 = IsoWorld.instance.CurrentCell.getGridSquare(var0, var1, var2);
         if (var3 != nullptr) {
            newGridSquare(var3);
         }
      }
   }

    static void debugLoadSquare(int var0, int var1, int var2) {
      if (Core.bDebug) {
    IsoGridSquare var3 = IsoWorld.instance.CurrentCell.getGridSquare(var0, var1, var2);
         if (var3 != nullptr) {
            loadGridSquare(var3);
         }
      }
   }

    static void debugLoadChunk(int var0, int var1) {
      if (Core.bDebug) {
    IsoChunk var2 = GameServer.bServer ? ServerMap.instance.getChunk(var0, var1) : IsoWorld.instance.CurrentCell.getChunk(var0, var1);
         if (var2 != nullptr) {
            for (int var3 = 0; var3 <= var2.maxLevel; var3++) {
               for (int var4 = 0; var4 < 10; var4++) {
                  for (int var5 = 0; var5 < 10; var5++) {
    IsoGridSquare var6 = var2.getGridSquare(var4, var5, var3);
                     if (var6 != nullptr && !var6.getObjects().empty()) {
                        loadGridSquare(var6);
                     }
                  }
               }
            }
         }
      }
   }

    static void reroute(Prototype var0, LuaClosure var1) {
      for (Callback var3 : onNew.values()) {
         for (int var4 = 0; var4 < var3.functions.size(); var4++) {
    LuaClosure var5 = (LuaClosure)var3.functions.get(var4);
            if (var5.prototype.filename == var0.filename) && var5.prototype.name == var0.name)) {
               var3.functions.set(var4, var1);
            }
         }
      }
   }

    static void Reset() {
      onNew.clear();
      onLoad.clear();
   }
}
} // namespace Lua
} // namespace zombie
