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
#include "zombie/util/Type.h"
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace worldMap {


class MapDefinitions {
public:
    static MapDefinitions instance;
   private const std::vector<std::string> m_definitions = std::make_unique<std::vector<>>();

    static MapDefinitions getInstance() {
      if (instance == nullptr) {
         instance = std::make_unique<MapDefinitions>();
      }

    return instance;
   }

    std::string pickRandom() {
      if (this.m_definitions.empty()) {
         this.initDefinitionsFromLua();
      }

      return this.m_definitions.empty() ? "Default" : (std::string)PZArrayUtil.pickRandom(this.m_definitions);
   }

    void initDefinitionsFromLua() {
    KahluaTable var1 = (KahluaTable)Type.tryCastTo(LuaManager.env.rawget("LootMaps"), KahluaTable.class);
      if (var1 != nullptr) {
    KahluaTable var2 = (KahluaTable)Type.tryCastTo(var1.rawget("Init"), KahluaTable.class);
         if (var2 != nullptr) {
    KahluaTableIterator var3 = var2.iterator();

            while (var3.advance()) {
    std::string var4 = (std::string)Type.tryCastTo(var3.getKey(), std::string.class);
               if (var4 != nullptr) {
                  this.m_definitions.push_back(var4);
               }
            }
         }
      }
   }

    static void Reset() {
      if (instance != nullptr) {
         instance.m_definitions.clear();
         instance = nullptr;
      }
   }
}
} // namespace worldMap
} // namespace zombie
