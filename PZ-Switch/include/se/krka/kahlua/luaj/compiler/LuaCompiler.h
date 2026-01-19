#pragma once
#include "org/luaj/kahluafork/compiler/LexState.h"
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaUtil.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"
#include "se/krka/kahlua/vm/LuaClosure.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace luaj {
namespace compiler {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class LuaCompiler {
public:
 static bool rewriteEvents = false;
 const int index;
 static const int LOADSTRING = 0;
 static const int LOADSTREAM = 1;
private
 static String[] names = new String[]{"loadstring", "loadstream"};
private
 static LuaCompiler[] functions = new LuaCompiler[names.length];

private
 LuaCompiler(int int0) { this->index = int0; }

 static void register(KahluaTable table) {
 for (int int0 = 0; int0 < names.length; int0++) {
 table.rawset(names[int0], functions[int0]);
 }
 }

 int call(LuaCallFrame luaCallFrame, int int0) {
 switch (this->index) {
 case 0:
 return this->loadstring(luaCallFrame, int0);
 case 1:
 return loadstream();
 default:
 return 0;
 }
 }

 static int loadstream(LuaCallFrame luaCallFrame, int int0) {
 try {
 KahluaUtil.luaAssert(int0 >= 2, "not enough arguments");
 void *object = luaCallFrame.get(0);
 KahluaUtil.luaAssert(object != nullptr, "No input given");
 std::string string = (String)luaCallFrame.get(1);
 if (dynamic_cast<Reader*>(object) != nullptr) {
 return luaCallFrame.push(loadis((Reader)object, string, nullptr,
 luaCallFrame.getEnvironment()));
 } else if (dynamic_cast<InputStream*>(object) != nullptr) {
 return luaCallFrame.push(loadis((InputStream)object, string, nullptr,
 luaCallFrame.getEnvironment()));
 } else {
 KahluaUtil.fail("Invalid type to loadstream: " + object.getClass());
 return 0;
 }
 } catch (RuntimeException runtimeException) {
 return luaCallFrame.push(nullptr, runtimeException.getMessage());
 } catch (IOException iOException) {
 return luaCallFrame.push(nullptr, iOException.getMessage());
 }
 }

 int loadstring(LuaCallFrame luaCallFrame, int int0) {
 try {
 KahluaUtil.luaAssert(int0 >= 1, "not enough arguments");
 std::string string0 = (String)luaCallFrame.get(0);
 KahluaUtil.luaAssert(string0 != nullptr, "No source given");
 std::string string1 = nullptr;
 if (int0 >= 2) {
 string1 = (String)luaCallFrame.get(1);
 }

 return luaCallFrame.push(
 loadstring(string0, string1, luaCallFrame.getEnvironment()));
 } catch (RuntimeException runtimeException) {
 return luaCallFrame.push(nullptr, runtimeException.getMessage());
 } catch (IOException iOException) {
 return luaCallFrame.push(nullptr, iOException.getMessage());
 }
 }

 static LuaClosure loadis(InputStream inputStream, std::string_view string,
 KahluaTable table) {
 return loadis();
 }

 static LuaClosure loadis(Reader reader, std::string_view string,
 KahluaTable table) {
 return loadis();
 }

 static LuaClosure loadstring(std::string_view string1,
 std::string_view string0, KahluaTable table) {
 return loadis(new ByteArrayInputStream(string1.getBytes("UTF-8");
 }

 static LuaClosure loadis(Reader reader, std::string_view string0,
 std::string_view string1, KahluaTable table) {
 return new LuaClosure(
 LexState.compile(reader.read(), reader, string0, string1), table);
 }

 static LuaClosure loadis(InputStream inputStream, std::string_view string0,
 std::string_view string1, KahluaTable table) {
 return loadis(new InputStreamReader(inputStream);
 }

 static {
 for (int int0 = 0; int0 < names.length; int0++) {
 functions[int0] = new LuaCompiler(int0);
 }
 }
}
} // namespace compiler
} // namespace luaj
} // namespace kahlua
} // namespace krka
} // namespace se
