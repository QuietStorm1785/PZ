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
namespace globalObjects {


class GlobalObject {
public:
    GlobalObjectSystem system;
    int x;
    int y;
    int z;
    const KahluaTable modData;

   GlobalObject(GlobalObjectSystem var1, int var2, int var3, int var4) {
      this.system = var1;
      this.x = var2;
      this.y = var3;
      this.z = var4;
      this.modData = LuaManager.platform.newTable();
   }

    GlobalObjectSystem getSystem() {
      return this.system;
   }

    void setLocation(int var1, int var2, int var3) {
   }

    int getX() {
      return this.x;
   }

    int getY() {
      return this.y;
   }

    int getZ() {
      return this.z;
   }

    KahluaTable getModData() {
      return this.modData;
   }

    void Reset() {
      this.system = nullptr;
      this.modData.wipe();
   }
}
} // namespace globalObjects
} // namespace zombie
