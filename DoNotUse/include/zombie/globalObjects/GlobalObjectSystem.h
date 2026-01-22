#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include <algorithm>

namespace zombie {
namespace globalObjects {


class GlobalObjectSystem {
public:
   private static const ArrayDeque<std::vector<GlobalObject>> objectListPool = std::make_unique<ArrayDeque<>>();
    const std::string name;
    const KahluaTable modData;
   protected const std::vector<GlobalObject> objects = std::make_unique<std::vector<>>();
    const GlobalObjectLookup lookup = std::make_shared<GlobalObjectLookup>(this);

   GlobalObjectSystem(std::string var1) {
      this.name = var1;
      this.modData = LuaManager.platform.newTable();
   }

    std::string getName() {
      return this.name;
   }

    KahluaTable getModData() {
      return this.modData;
   }

   protected abstract GlobalObject makeObject(int var1, int var2, int var3);

    GlobalObject newObject(int var1, int var2, int var3) {
      if (this.getObjectAt(var1, var2, var3) != nullptr) {
         throw IllegalStateException("already an object at " + var1 + "," + var2 + "," + var3);
      } else {
    GlobalObject var4 = this.makeObject(var1, var2, var3);
         this.objects.push_back(var4);
         this.lookup.addObject(var4);
    return var4;
      }
   }

    void removeObject(GlobalObject var1) {
      if (var1 == nullptr) {
         throw NullPointerException("object is nullptr");
      } else if (var1.system != this) {
         throw IllegalStateException("object not in this system");
      } else {
         this.objects.remove(var1);
         this.lookup.removeObject(var1);
         var1.Reset();
      }
   }

    GlobalObject getObjectAt(int var1, int var2, int var3) {
      return this.lookup.getObjectAt(var1, var2, var3);
   }

    bool hasObjectsInChunk(int var1, int var2) {
      return this.lookup.hasObjectsInChunk(var1, var2);
   }

   public const std::vector<GlobalObject> getObjectsInChunk(int var1, int var2) {
      return this.lookup.getObjectsInChunk(var1, var2, this.allocList());
   }

   public const std::vector<GlobalObject> getObjectsAdjacentTo(int var1, int var2, int var3) {
      return this.lookup.getObjectsAdjacentTo(var1, var2, var3, this.allocList());
   }

    int getObjectCount() {
      return this.objects.size();
   }

    GlobalObject getObjectByIndex(int var1) {
      return var1 >= 0 && var1 < this.objects.size() ? this.objects.get(var1) : nullptr;
   }

   public const std::vector<GlobalObject> allocList() {
      return objectListPool.empty() ? std::make_unique<std::vector<>>() : objectListPool.pop();
   }

    void finishedWithList(std::vector<GlobalObject> var1) {
      if (var1 != nullptr && !objectListPool.contains(var1)) {
         var1.clear();
         objectListPool.push_back(var1);
      }
   }

    void Reset() {
      for (int var1 = 0; var1 < this.objects.size(); var1++) {
    GlobalObject var2 = this.objects.get(var1);
         var2.Reset();
      }

      this.objects.clear();
      this.modData.wipe();
   }
}
} // namespace globalObjects
} // namespace zombie
