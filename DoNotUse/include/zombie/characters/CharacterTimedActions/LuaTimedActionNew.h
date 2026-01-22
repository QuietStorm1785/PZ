#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/ai/astar/IPathfinder.h"
#include "zombie/ai/astar/Mover.h"
#include "zombie/ai/astar/Path.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"

namespace zombie {
namespace characters {
namespace CharacterTimedActions {


class LuaTimedActionNew : public BaseAction {
public:
    KahluaTable table;

    public LuaTimedActionNew(KahluaTable var1, IsoGameCharacter var2) {
      super(var2);
      this.table = var1;
    void* var3 = var1.rawget("maxTime");
      this.MaxTime = (int)LuaManager.converterManager.fromLuaToJava(var3, int.class);
    void* var4 = var1.rawget("stopOnWalk");
    void* var5 = var1.rawget("stopOnRun");
    void* var6 = var1.rawget("stopOnAim");
    void* var7 = var1.rawget("caloriesModifier");
    void* var8 = var1.rawget("useProgressBar");
    void* var9 = var1.rawget("forceProgressBar");
    void* var10 = var1.rawget("loopedAction");
      if (var4 != nullptr) {
         this.StopOnWalk = (bool)LuaManager.converterManager.fromLuaToJava(var4, bool.class);
      }

      if (var5 != nullptr) {
         this.StopOnRun = (bool)LuaManager.converterManager.fromLuaToJava(var5, bool.class);
      }

      if (var6 != nullptr) {
         this.StopOnAim = (bool)LuaManager.converterManager.fromLuaToJava(var6, bool.class);
      }

      if (var7 != nullptr) {
         this.caloriesModifier = (float)LuaManager.converterManager.fromLuaToJava(var7, float.class);
      }

      if (var8 != nullptr) {
         this.UseProgressBar = (bool)LuaManager.converterManager.fromLuaToJava(var8, bool.class);
      }

      if (var9 != nullptr) {
         this.ForceProgressBar = (bool)LuaManager.converterManager.fromLuaToJava(var9, bool.class);
      }

      if (var10 != nullptr) {
         this.loopAction = (bool)LuaManager.converterManager.fromLuaToJava(var10, bool.class);
      }
   }

    void waitToStart() {
    bool var1 = LuaManager.caller.protectedCallBoolean(LuaManager.thread, this.table.rawget("waitToStart"), this.table);
      if (var1 == bool.FALSE) {
         super.waitToStart();
      }
   }

    void update() {
      super.update();
      LuaManager.caller.pcallvoid(LuaManager.thread, this.table.rawget("update"), this.table);
   }

    bool valid() {
      Object[] var1 = LuaManager.caller.pcall(LuaManager.thread, this.table.rawget("isValid"), this.table);
      return var1.length > 1 && var1[1] instanceof bool && (bool)var1[1];
   }

    void start() {
      super.start();
      this.CurrentTime = 0.0F;
      LuaManager.caller.pcall(LuaManager.thread, this.table.rawget("start"), this.table);
   }

    void stop() {
      super.stop();
      LuaManager.caller.pcall(LuaManager.thread, this.table.rawget("stop"), this.table);
   }

    void perform() {
      super.perform();
      LuaManager.caller.pcall(LuaManager.thread, this.table.rawget("perform"), this.table);
   }

    void Failed(Mover var1) {
      this.table.rawset("path", nullptr);
      LuaManager.caller.pcallvoid(LuaManager.thread, this.table.rawget("failedPathfind"), this.table);
   }

    void Succeeded(Path var1, Mover var2) {
      this.table.rawset("path", var1);
      LuaManager.caller.pcallvoid(LuaManager.thread, this.table.rawget("succeededPathfind"), this.table);
   }

    void Pathfind(IsoGameCharacter var1, int var2, int var3, int var4) {
   }

    std::string getName() {
      return "timedActionPathfind";
   }

    void setCurrentTime(float var1) {
      this.CurrentTime = PZMath.clamp(var1, 0.0F, this.MaxTime);
   }

    void setTime(int var1) {
      this.MaxTime = var1;
   }

    void OnAnimEvent(AnimEvent var1) {
    void* var2 = this.table.rawget("animEvent");
      if (var2 != nullptr) {
         LuaManager.caller.pcallvoid(LuaManager.thread, var2, this.table, var1.m_EventName, var1.m_ParameterValue);
      }
   }

    std::string getMetaType() {
      return this.table != nullptr && this.table.getMetatable() != nullptr ? this.table.getMetatable().getString("Type") : "";
   }
}
} // namespace CharacterTimedActions
} // namespace characters
} // namespace zombie
