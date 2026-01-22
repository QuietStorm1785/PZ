#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoGameCharacter.h"

namespace zombie {
namespace characters {
namespace CharacterTimedActions {


class LuaTimedAction : public BaseAction {
public:
    KahluaTable table;
   public static Object[] statObj = new Object[6];

    public LuaTimedAction(KahluaTable var1, IsoGameCharacter var2) {
      super(var2);
      this.table = var1;
    void* var3 = var1.rawget("maxTime");
      this.MaxTime = (int)LuaManager.converterManager.fromLuaToJava(var3, int.class);
    void* var4 = var1.rawget("stopOnWalk");
    void* var5 = var1.rawget("stopOnRun");
    void* var6 = var1.rawget("stopOnAim");
    void* var7 = var1.rawget("onUpdateFunc");
      if (var4 != nullptr) {
         this.StopOnWalk = (bool)LuaManager.converterManager.fromLuaToJava(var4, bool.class);
      }

      if (var5 != nullptr) {
         this.StopOnRun = (bool)LuaManager.converterManager.fromLuaToJava(var5, bool.class);
      }

      if (var6 != nullptr) {
         this.StopOnAim = (bool)LuaManager.converterManager.fromLuaToJava(var6, bool.class);
      }
   }

    void update() {
      statObj[0] = this.table.rawget("character");
      statObj[1] = this.table.rawget("param1");
      statObj[2] = this.table.rawget("param2");
      statObj[3] = this.table.rawget("param3");
      statObj[4] = this.table.rawget("param4");
      statObj[5] = this.table.rawget("param5");
      LuaManager.caller.pcallvoid(LuaManager.thread, this.table.rawget("onUpdateFunc"), statObj);
      super.update();
   }

    bool valid() {
      Object[] var1 = LuaManager.caller
         .pcall(
            LuaManager.thread,
            this.table.rawget("isValidFunc"),
            new Object[]{
               this.table.rawget("character"),
               this.table.rawget("param1"),
               this.table.rawget("param2"),
               this.table.rawget("param3"),
               this.table.rawget("param4"),
               this.table.rawget("param5")
            }
         );
      return var1.length > 0 && (bool)var1[0];
   }

    void start() {
      super.start();
      this.CurrentTime = 0.0F;
      LuaManager.caller
         .pcall(
            LuaManager.thread,
            this.table.rawget("startFunc"),
            new Object[]{
               this.table.rawget("character"),
               this.table.rawget("param1"),
               this.table.rawget("param2"),
               this.table.rawget("param3"),
               this.table.rawget("param4"),
               this.table.rawget("param5")
            }
         );
   }

    void stop() {
      super.stop();
      LuaManager.caller
         .pcall(
            LuaManager.thread,
            this.table.rawget("onStopFunc"),
            new Object[]{
               this.table.rawget("character"),
               this.table.rawget("param1"),
               this.table.rawget("param2"),
               this.table.rawget("param3"),
               this.table.rawget("param4"),
               this.table.rawget("param5")
            }
         );
   }

    void perform() {
      super.perform();
      LuaManager.caller
         .pcall(
            LuaManager.thread,
            this.table.rawget("performFunc"),
            new Object[]{
               this.table.rawget("character"),
               this.table.rawget("param1"),
               this.table.rawget("param2"),
               this.table.rawget("param3"),
               this.table.rawget("param4"),
               this.table.rawget("param5")
            }
         );
   }
}
} // namespace CharacterTimedActions
} // namespace characters
} // namespace zombie
