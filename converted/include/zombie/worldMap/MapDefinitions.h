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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class MapDefinitions {
public:
 static MapDefinitions instance;
 private ArrayList<String> m_definitions = std::make_unique<ArrayList<>>();

 static MapDefinitions getInstance() {
 if (instance == nullptr) {
 instance = std::make_unique<MapDefinitions>();
 }

 return instance;
 }

 std::string pickRandom() {
 if (this->m_definitions.empty()) {
 this->initDefinitionsFromLua();
 }

 return this->m_definitions.empty() ? "Default" : PZArrayUtil.pickRandom(this->m_definitions);
 }

 void initDefinitionsFromLua() {
 KahluaTable table0 = Type.tryCastTo(LuaManager.env.rawget("LootMaps"), KahluaTable.class);
 if (table0 != nullptr) {
 KahluaTable table1 = Type.tryCastTo(table0.rawget("Init"), KahluaTable.class);
 if (table1 != nullptr) {
 KahluaTableIterator kahluaTableIterator = table1.iterator();

 while (kahluaTableIterator.advance()) {
 std::string string = Type.tryCastTo(kahluaTableIterator.getKey(), String.class);
 if (string != nullptr) {
 this->m_definitions.add(string);
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
