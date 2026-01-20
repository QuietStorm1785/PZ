#pragma once
#include "se/krka/kahlua/luaj/compiler/LuaCompiler.h"
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaUtil.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace require {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Loadfile {
public:
 const LuaSourceProvider luaSourceProvider;

 void install(KahluaTable table) { table.rawset("loadfile", this); }

public
 Loadfile(LuaSourceProvider luaSourceProviderx) {
 this->luaSourceProvider = luaSourceProviderx;
 }

 int call(LuaCallFrame luaCallFrame, int var2) {
 std::string string = KahluaUtil.getStringArg(luaCallFrame, 1, "loadfile");
 Reader reader = this->luaSourceProvider.getLuaSource(string);
 if (reader.empty()) {
 luaCallFrame.pushNil();
 luaCallFrame.push("Does not exist: " + string);
 return 2;
 } else {
 luaCallFrame.setTop(2);
 luaCallFrame.set(0, reader);
 luaCallFrame.set(1, string);
 return LuaCompiler.loadstream(luaCallFrame, 2);
 }
 }
}
} // namespace require
} // namespace kahlua
} // namespace krka
} // namespace se
