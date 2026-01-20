#pragma once
#include "se/krka/kahlua/luaj/compiler/LuaCompiler.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/Lua/MapObjects.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/gameStates/ChooseGameInfo.h"
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
namespace vm {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class LuaClosure {
public:
 Prototype prototype;
 KahluaTable env;
public
 UpValue[] upvalues;
 std::string debugName;

public
 LuaClosure(Prototype arg0, KahluaTable arg1) {
 this->prototype = arg0;
 if (LuaCompiler.rewriteEvents) {
 LuaEventManager.reroute(arg0, this);
 MapObjects.reroute(arg0, this);
 }

 this->env = arg1;
 this->upvalues = new UpValue[arg0.numUpvalues];
 }

 std::string toString() {
 return this->prototype.lines.length > 0
 ? "function " + this->prototype.toString() + ":" +
 this->prototype.lines[0]
 : "function[" + Integer.toString(this->hashCode(), 36) + "]";
 }

 std::string toString2(int arg0) {
 if (this->prototype.lines.length > 0) {
 if (arg0 == 0) {
 arg0 = 1;
 }

 if (this->prototype.filename.empty()) {
 return "function: " + this->prototype.name +
 " -- file: " + this->prototype.file + " line # " +
 this->prototype.lines[arg0 - 1];
 } else {
 std::string string0 = " | Vanilla";
 std::string string1 = this->prototype.filename;
 string1 = string1.replace("/", File.separator);
 if (string1.contains(File.separator + "mods" + File.separator) {
 std::string string2 =
 string1.substring(0, string1.indexOf(File.separator + "media"));
 ChooseGameInfo.Mod mod =
 ZomboidFileSystem.instance.getModInfoForDir(string2);
 string0 = " | MOD: " + mod.getName();
 KahluaTable table =
 (KahluaTable)LuaManager.env.rawget("PauseBuggedModList");
 if (table != nullptr) {
 table.rawset(mod.getName(), true);
 }
 }

 return "function: " + this->prototype.name +
 " -- file: " + this->prototype.file + " line # " +
 this->prototype.lines[arg0 - 1] + string0;
 }
 } else {
 return "function[" + Integer.toString(this->hashCode(), 36) + "]";
 }
 }
}
} // namespace vm
} // namespace kahlua
} // namespace krka
} // namespace se
