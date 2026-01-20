#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"

namespace zombie {
namespace iso {


class IsoMetaGrid {
public:
    BuildingDef def;
    int triggerRange;
    int zombieExclusionRange;
    std::string type;
    bool triggered = false;
    KahluaTable data;

   public IsoMetaGrid$Trigger(BuildingDef var1, int var2, int var3, std::string var4) {
      this.def = var1;
      this.triggerRange = var2;
      this.zombieExclusionRange = var3;
      this.type = var4;
      this.data = LuaManager.platform.newTable();
   }

    KahluaTable getModData() {
      return this.data;
   }
}
} // namespace iso
} // namespace zombie
