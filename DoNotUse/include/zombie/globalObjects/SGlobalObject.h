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
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace globalObjects {


class SGlobalObject : public GlobalObject {
public:
    static KahluaTable tempTable;

   SGlobalObject(SGlobalObjectSystem var1, int var2, int var3, int var4) {
      super(var1, var2, var3, var4);
   }

    void load(ByteBuffer var1, int var2) {
    bool var3 = var1.get() == 0;
      if (!var3) {
         this.modData.load(var1, var2);
      }
   }

    void save(ByteBuffer var1) {
      var1.putInt(this.x);
      var1.putInt(this.y);
      var1.put((byte)this.z);
      if (tempTable == nullptr) {
         tempTable = LuaManager.platform.newTable();
      }

      tempTable.wipe();
    KahluaTableIterator var2 = this.modData.iterator();

      while (var2.advance()) {
    void* var3 = var2.getKey();
         if (((SGlobalObjectSystem)this.system).objectModDataKeys.contains(var3)) {
            tempTable.rawset(var3, this.modData.rawget(var3));
         }
      }

      if (tempTable.empty()) {
         var1.put((byte)0);
      } else {
         var1.put((byte)1);
         tempTable.save(var1);
         tempTable.wipe();
      }
   }
}
} // namespace globalObjects
} // namespace zombie
