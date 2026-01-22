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
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/BoxedStaticValues.h"

namespace zombie {
namespace globalObjects {


class CGlobalObjectSystem : public GlobalObjectSystem {
public:
    public CGlobalObjectSystem(const std::string& var1) {
      super(var1);
   }

    GlobalObject makeObject(int var1, int var2, int var3) {
      return std::make_shared<CGlobalObject>(this, var1, var2, var3);
   }

    void sendCommand(const std::string& var1, IsoPlayer var2, KahluaTable var3) {
      CGlobalObjectNetwork.sendClientCommand(var2, this.name, var1, var3);
   }

    void receiveServerCommand(const std::string& var1, KahluaTable var2) {
    void* var3 = this.modData.rawget("OnServerCommand");
      if (var3 == nullptr) {
         throw IllegalStateException("OnServerCommand method undefined for system '" + this.name + "'");
      } else {
         LuaManager.caller.pcallvoid(LuaManager.thread, var3, this.modData, var1, var2);
      }
   }

    void receiveNewLuaObjectAt(int var1, int var2, int var3, KahluaTable var4) {
    void* var5 = this.modData.rawget("newLuaObjectAt");
      if (var5 == nullptr) {
         throw IllegalStateException("newLuaObjectAt method undefined for system '" + this.name + "'");
      } else {
         LuaManager.caller
            .pcall(
               LuaManager.thread,
               var5,
               new Object[]{this.modData, BoxedStaticValues.toDouble(var1), BoxedStaticValues.toDouble(var2), BoxedStaticValues.toDouble(var3)}
            );
    GlobalObject var6 = this.getObjectAt(var1, var2, var3);
         if (var6 != nullptr) {
    KahluaTableIterator var7 = var4.iterator();

            while (var7.advance()) {
               var6.getModData().rawset(var7.getKey(), var7.getValue());
            }
         }
      }
   }

    void receiveRemoveLuaObjectAt(int var1, int var2, int var3) {
    void* var4 = this.modData.rawget("removeLuaObjectAt");
      if (var4 == nullptr) {
         throw IllegalStateException("removeLuaObjectAt method undefined for system '" + this.name + "'");
      } else {
         LuaManager.caller
            .pcall(
               LuaManager.thread,
               var4,
               new Object[]{this.modData, BoxedStaticValues.toDouble(var1), BoxedStaticValues.toDouble(var2), BoxedStaticValues.toDouble(var3)}
            );
      }
   }

    void receiveUpdateLuaObjectAt(int var1, int var2, int var3, KahluaTable var4) {
    GlobalObject var5 = this.getObjectAt(var1, var2, var3);
      if (var5 != nullptr) {
    KahluaTableIterator var6 = var4.iterator();

         while (var6.advance()) {
            var5.getModData().rawset(var6.getKey(), var6.getValue());
         }

    void* var7 = this.modData.rawget("OnLuaObjectUpdated");
         if (var7 == nullptr) {
            throw IllegalStateException("OnLuaObjectUpdated method undefined for system '" + this.name + "'");
         } else {
            LuaManager.caller.pcall(LuaManager.thread, var7, new Object[]{this.modData, var5.getModData()});
         }
      }
   }

    void Reset() {
      super.Reset();
      this.modData.wipe();
   }
}
} // namespace globalObjects
} // namespace zombie
