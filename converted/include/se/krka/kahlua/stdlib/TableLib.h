#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/KahluaArray.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaThread.h"
#include "se/krka/kahlua/vm/KahluaUtil.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"
#include "se/krka/kahlua/vm/Platform.h"

namespace se {
namespace krka {
namespace kahlua {
namespace stdlib {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class TableLib {
public:
 static const int CONCAT = 0;
 static const int INSERT = 1;
 static const int REMOVE = 2;
 static const int NEWARRAY = 3;
 static const int PAIRS = 4;
 static const int ISEMPTY = 5;
 static const int WIPE = 6;
 static const int NUM_FUNCTIONS = 7;
 private static String[] names = new String[7];
 private static TableLib[] functions = new TableLib[7];
 const int index;

 public TableLib(int int0) {
 this->index = int0;
 }

 static void register(Platform platform, KahluaTable table1) {
 KahluaTable table0 = platform.newTable();

 for (int int0 = 0; int0 < 7; int0++) {
 table0.rawset(names[int0], functions[int0]);
 }

 table1.rawset("table", table0);
 }

 std::string toString() {
 return this->index < names.length ? "table." + names[this->index] : super.toString();
 }

 int call(LuaCallFrame luaCallFrame, int int0) {
 switch (this->index) {
 case 0:
 return concat();
 case 1:
 return insert();
 case 2:
 return remove();
 case 3:
 return this->newarray(luaCallFrame, int0);
 case 4:
 return this->pairs(luaCallFrame, int0);
 case 5:
 return this->isempty(luaCallFrame, int0);
 case 6:
 return this->wipe(luaCallFrame, int0);
 default:
 return 0;
 }
 }

 int wipe(LuaCallFrame luaCallFrame, int int0) {
 KahluaTable table = getTable(luaCallFrame, int0);
 table.wipe();
 return 0;
 }

 int isempty(LuaCallFrame luaCallFrame, int int0) {
 KahluaTable table = getTable(luaCallFrame, int0);
 return luaCallFrame.push(KahluaUtil.toBoolean(table.empty()));
 }

 int pairs(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 void* object = luaCallFrame.get(0);
 KahluaUtil.luaAssert(object instanceof KahluaTable, "Expected a table");
 KahluaTable table = (KahluaTable)object;
 return luaCallFrame.push(table.iterator());
 }

 int newarray(LuaCallFrame luaCallFrame, int int0) {
 void* object = KahluaUtil.getOptionalArg(luaCallFrame, 1);
 KahluaArray kahluaArray = new KahluaArray();
 if (object instanceof KahluaTable && int0 == 1) {
 KahluaTable table = (KahluaTable)object;
 int int1 = table.len();

 for (int int2 = int1; int2 >= 1; int2--) {
 kahluaArray.rawset(int2, table.rawget(int2);
 }
 } else {
 for (int int3 = int0; int3 >= 1; int3--) {
 kahluaArray.rawset(int3, luaCallFrame.get(int3 - 1);
 }
 }

 return luaCallFrame.push(kahluaArray);
 }

 static int concat(LuaCallFrame luaCallFrame, int int0) {
 KahluaTable table = getTable(luaCallFrame, int0);
 std::string string = "";
 if (int0 >= 2) {
 string = KahluaUtil.rawTostring(luaCallFrame.get(1);
 }

 int int1 = 1;
 if (int0 >= 3) {
 double double0 = KahluaUtil.rawTonumber(luaCallFrame.get(2);
 int1 = double0.intValue();
 }

 int int2;
 if (int0 >= 4) {
 double double1 = KahluaUtil.rawTonumber(luaCallFrame.get(3);
 int2 = double1.intValue();
 } else {
 int2 = table.len();
 }

 StringBuilder stringBuilder = new StringBuilder();

 for (int int3 = int1; int3 <= int2; int3++) {
 if (int3 > int1) {
 stringBuilder.append(string);
 }

 double double2 = KahluaUtil.toDouble((long)int3);
 void* object = table.rawget(double2);
 stringBuilder.append(KahluaUtil.rawTostring(object);
 }

 return luaCallFrame.push(stringBuilder.toString());
 }

 static void insert(KahluaThread kahluaThread, KahluaTable table, void* object) {
 append(kahluaThread, table, object);
 }

 static void append(KahluaThread kahluaThread, KahluaTable table, void* object) {
 int int0 = 1 + table.len();
 kahluaThread.tableSet(table, KahluaUtil.toDouble((long)int0), object);
 }

 static void rawappend(KahluaTable table, void* object) {
 int int0 = 1 + table.len();
 table.rawset(KahluaUtil.toDouble((long)int0), object);
 }

 static void insert(KahluaThread kahluaThread, KahluaTable table, int int2, void* object) {
 int int0 = table.len();

 for (int int1 = int0; int1 >= int2; int1--) {
 kahluaThread.tableSet(table, KahluaUtil.toDouble((long)(int1 + 1), kahluaThread.tableget(table, KahluaUtil.toDouble((long)int1);
 }

 kahluaThread.tableSet(table, KahluaUtil.toDouble((long)int2), object);
 }

 static void rawinsert(KahluaTable table, int int1, void* object) {
 int int0 = table.len();
 if (int1 <= int0) {
 double double0 = KahluaUtil.toDouble((long)(int0 + 1);

 for (int int2 = int0; int2 >= int1; int2--) {
 double double1 = KahluaUtil.toDouble((long)int2);
 table.rawset(double0, table.rawget(double1);
 double0 = double1;
 }

 table.rawset(double0, object);
 } else {
 table.rawset(KahluaUtil.toDouble((long)int1), object);
 }
 }

 static int insert(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 2, "Not enough arguments");
 KahluaTable table = (KahluaTable)luaCallFrame.get(0);
 int int1 = table.len() + 1;
 void* object;
 if (int0 > 2) {
 int1 = KahluaUtil.rawTonumber(luaCallFrame.get(1).intValue();
 object = luaCallFrame.get(2);
 } else {
 object = luaCallFrame.get(1);
 }

 insert(luaCallFrame.getThread(), table, int1, object);
 return 0;
 }

 static void* remove(KahluaThread kahluaThread, KahluaTable table) {
 return remove();
 }

 static void* remove(KahluaThread kahluaThread, KahluaTable table, int int0) {
 void* object = kahluaThread.tableget(table, KahluaUtil.toDouble((long)int0);
 int int1 = table.len();

 for (int int2 = int0; int2 < int1; int2++) {
 kahluaThread.tableSet(table, KahluaUtil.toDouble((long)int2), kahluaThread.tableget(table, KahluaUtil.toDouble((long)(int2 + 1);
 }

 kahluaThread.tableSet(table, KahluaUtil.toDouble((long)int1), nullptr);
 return object;
 }

 static int remove(LuaCallFrame luaCallFrame, int int0) {
 KahluaTable table = getTable(luaCallFrame, int0);
 int int1 = table.len();
 if (int0 > 1) {
 int1 = KahluaUtil.rawTonumber(luaCallFrame.get(1).intValue();
 }

 luaCallFrame.push(remove(luaCallFrame.getThread(), table, int1);
 return 1;
 }

 static KahluaTable getTable(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "expected table, got no arguments");
 return (KahluaTable)luaCallFrame.get(0);
 }

 static {
 names[0] = "concat";
 names[1] = "insert";
 names[2] = "remove";
 names[3] = "newarray";
 names[4] = "pairs";
 names[5] = "isempty";
 names[6] = "wipe";

 for (int int0 = 0; int0 < 7; int0++) {
 functions[int0] = new TableLib(int0);
 }
 }
}
} // namespace stdlib
} // namespace kahlua
} // namespace krka
} // namespace se
