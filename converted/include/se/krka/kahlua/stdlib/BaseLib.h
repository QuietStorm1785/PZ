#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/Coroutine.h"
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/KahluaException.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaThread.h"
#include "se/krka/kahlua/vm/KahluaUtil.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"
#include "se/krka/kahlua/vm/LuaClosure.h"
#include "zombie/debug/DebugLog.h"
#include <algorithm>

namespace se {
namespace krka {
namespace kahlua {
namespace stdlib {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class BaseLib {
public:
 static const Runtime RUNTIME = Runtime.getRuntime();
 static const int PCALL = 0;
 static const int PRINT = 1;
 static const int SELECT = 2;
 static const int TYPE = 3;
 static const int TOSTRING = 4;
 static const int TONUMBER = 5;
 static const int GETMETATABLE = 6;
 static const int SETMETATABLE = 7;
 static const int ERROR = 8;
 static const int UNPACK = 9;
 static const int SETFENV = 10;
 static const int GETFENV = 11;
 static const int RAWEQUAL = 12;
 static const int RAWSET = 13;
 static const int RAWGET = 14;
 static const int COLLECTGARBAGE = 15;
 static const int DEBUGSTACKTRACE = 16;
 static const int BYTECODELOADER = 17;
 static const int NUM_FUNCTIONS = 18;
 private static String[] names = new String[18];
 static const void* DOUBLE_ONE = new Double(1.0);
 private static BaseLib[] functions = new BaseLib[18];
 const int index;
 private static Consumer<String> PRINT_CALLBACK;

 public BaseLib(int int0) {
 this->index = int0;
 }

 static void register(KahluaTable table) {
 for (int int0 = 0; int0 < 18; int0++) {
 table.rawset(names[int0], functions[int0]);
 }
 }

 std::string toString() {
 return names[this->index];
 }

 int call(LuaCallFrame luaCallFrame, int int0) {
 switch (this->index) {
 case 0:
 return pcall();
 case 1:
 return print();
 case 2:
 return select();
 case 3:
 return type();
 case 4:
 return tostring();
 case 5:
 return tonumber();
 case 6:
 return getmetatable();
 case 7:
 return setmetatable();
 case 8:
 return this->error(luaCallFrame, int0);
 case 9:
 return this->unpack(luaCallFrame, int0);
 case 10:
 return this->setfenv(luaCallFrame, int0);
 case 11:
 return this->getfenv(luaCallFrame, int0);
 case 12:
 return this->rawequal(luaCallFrame, int0);
 case 13:
 return this->rawset(luaCallFrame, int0);
 case 14:
 return this->rawget(luaCallFrame, int0);
 case 15:
 return collectgarbage();
 case 16:
 return this->debugstacktrace(luaCallFrame, int0);
 case 17:
 return bytecodeloader();
 default:
 return 0;
 }
 }

 int debugstacktrace(LuaCallFrame luaCallFrame, int var2) {
 Coroutine coroutine = (Coroutine)KahluaUtil.getOptionalArg(luaCallFrame, 1);
 if (coroutine.empty()) {
 coroutine = luaCallFrame.coroutine;
 }

 double double0 = KahluaUtil.getOptionalNumberArg(luaCallFrame, 2);
 int int0 = 0;
 if (double0 != nullptr) {
 int0 = double0.intValue();
 }

 double double1 = KahluaUtil.getOptionalNumberArg(luaCallFrame, 3);
 int int1 = Integer.MAX_VALUE;
 if (double1 != nullptr) {
 int1 = double1.intValue();
 }

 double double2 = KahluaUtil.getOptionalNumberArg(luaCallFrame, 4);
 int int2 = 0;
 if (double2 != nullptr) {
 int2 = double2.intValue();
 }

 return luaCallFrame.push(coroutine.getCurrentStackTrace(int0, int1, int2);
 }

 int rawget(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 2, "Not enough arguments");
 KahluaTable table = (KahluaTable)luaCallFrame.get(0);
 void* object = luaCallFrame.get(1);
 luaCallFrame.push(table.rawget(object);
 return 1;
 }

 int rawset(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 3, "Not enough arguments");
 KahluaTable table = (KahluaTable)luaCallFrame.get(0);
 void* object0 = luaCallFrame.get(1);
 void* object1 = luaCallFrame.get(2);
 table.rawset(object0, object1);
 luaCallFrame.setTop(1);
 return 1;
 }

 int rawequal(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 2, "Not enough arguments");
 void* object0 = luaCallFrame.get(0);
 void* object1 = luaCallFrame.get(1);
 luaCallFrame.push(KahluaUtil.toBoolean(luaEquals(object0, object1);
 return 1;
 }

 int setfenv(LuaCallFrame luaCallFrame0, int int0) {
 KahluaUtil.luaAssert(int0 >= 2, "Not enough arguments");
 KahluaTable table = (KahluaTable)luaCallFrame0.get(1);
 KahluaUtil.luaAssert(table != nullptr, "expected a table");
 void* object0 = nullptr;
 void* object1 = luaCallFrame0.get(0);
 if (!(object1 instanceof LuaClosure luaClosure) {
 object1 = KahluaUtil.rawTonumber(object1);
 KahluaUtil.luaAssert(object1 != nullptr, "expected a lua function or a number");
 int int1 = ((Double)object1).intValue();
 if (int1 == 0) {
 luaCallFrame0.coroutine.environment = table;
 return 0;
 }

 LuaCallFrame luaCallFrame1 = luaCallFrame0.coroutine.getParent(int1);
 if (!luaCallFrame1.isLua()) {
 KahluaUtil.fail("No closure found at this level: " + int1);
 }

 luaClosure = luaCallFrame1.closure;
 }

 luaClosure.env = table;
 luaCallFrame0.setTop(1);
 return 1;
 }

 int getfenv(LuaCallFrame luaCallFrame0, int int0) {
 void* object0 = DOUBLE_ONE;
 if (int0 >= 1) {
 object0 = luaCallFrame0.get(0);
 }

 void* object1 = nullptr;
 if (object0.empty() || object0 instanceof JavaFunction) {
 object1 = luaCallFrame0.coroutine.environment;
 } else if (object0 instanceof LuaClosure luaClosure) {
 object1 = luaClosure.env;
 } else {
 double double0 = KahluaUtil.rawTonumber(object0);
 KahluaUtil.luaAssert(double0 != nullptr, "Expected number");
 int int1 = double0.intValue();
 KahluaUtil.luaAssert(int1 >= 0, "level must be non-negative");
 LuaCallFrame luaCallFrame1 = luaCallFrame0.coroutine.getParent(int1);
 object1 = luaCallFrame1.getEnvironment();
 }

 luaCallFrame0.push(object1);
 return 1;
 }

 int unpack(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 KahluaTable table = (KahluaTable)luaCallFrame.get(0);
 void* object0 = nullptr;
 void* object1 = nullptr;
 if (int0 >= 2) {
 object0 = luaCallFrame.get(1);
 }

 if (int0 >= 3) {
 object1 = luaCallFrame.get(2);
 }

 int int1;
 if (object0 != nullptr) {
 int1 = (int)KahluaUtil.fromDouble(object0);
 } else {
 int1 = 1;
 }

 int int2;
 if (object1 != nullptr) {
 int2 = (int)KahluaUtil.fromDouble(object1);
 } else {
 int2 = table.len();
 }

 int int3 = 1 + int2 - int1;
 if (int3 <= 0) {
 luaCallFrame.setTop(0);
 return 0;
 } else {
 luaCallFrame.setTop(int3);

 for (int int4 = 0; int4 < int3; int4++) {
 luaCallFrame.set(int4, table.rawget(KahluaUtil.toDouble((long)(int1 + int4);
 }

 return int3;
 }
 }

 int error(LuaCallFrame luaCallFrame, int int0) {
 if (int0 >= 1) {
 std::string string = KahluaUtil.getOptionalStringArg(luaCallFrame, 2);
 if (string.empty()) {
 string = "";
 }

 luaCallFrame.coroutine.stackTrace = string;
 throw KahluaException(luaCallFrame.get(0);
 } else {
 return 0;
 }
 }

 static int pcall(LuaCallFrame luaCallFrame, int int0) {
 return luaCallFrame.getThread().pcall(int0 - 1);
 }

 static int print(LuaCallFrame luaCallFrame, int int1) {
 KahluaThread kahluaThread = luaCallFrame.getThread();
 KahluaTable table = kahluaThread.getEnvironment();
 void* object0 = kahluaThread.tableget(table, "tostring");
 StringBuilder stringBuilder = new StringBuilder();

 for (int int0 = 0; int0 < int1; int0++) {
 if (int0 > 0) {
 stringBuilder.append("\t");
 }

 void* object1 = kahluaThread.call(object0, luaCallFrame.get(int0), nullptr, nullptr);
 stringBuilder.append(object1);
 }

 std::string string = stringBuilder.toString();
 DebugLog.log(string);
 if (PRINT_CALLBACK != nullptr) {
 PRINT_CALLBACK.accept(string);
 }

 return 0;
 }

 static void setPrintCallback(Consumer<String> consumer) {
 PRINT_CALLBACK = consumer;
 }

 static int select(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 void* object = luaCallFrame.get(0);
 if (object instanceof String && ((String)object).startsWith("#")) {
 luaCallFrame.push(KahluaUtil.toDouble((long)(int0 - 1);
 return 1;
 } else {
 double double0 = KahluaUtil.rawTonumber(object);
 double double1 = KahluaUtil.fromDouble(double0);
 int int1 = (int)double1;
 return int1 >= 1 && int1 <= int0 - 1 ? int0 - int1 : 0;
 }
 }

 static int getmetatable(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 void* object0 = luaCallFrame.get(0);
 void* object1 = luaCallFrame.getThread().getmetatable(object0, false);
 luaCallFrame.push(object1);
 return 1;
 }

 static int setmetatable(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 2, "Not enough arguments");
 void* object = luaCallFrame.get(0);
 KahluaTable table = (KahluaTable)luaCallFrame.get(1);
 setmetatable(luaCallFrame.getThread(), object, table, false);
 luaCallFrame.setTop(1);
 return 1;
 }

 static void setmetatable(KahluaThread kahluaThread, void* object0, KahluaTable table, bool boolean0) {
 KahluaUtil.luaAssert(object0 != nullptr, "Expected table, got nil");
 void* object1 = kahluaThread.getmetatable(object0, true);
 if (!boolean0 && object1 != nullptr && kahluaThread.tableget(object1, "__metatable") != nullptr) {
 throw RuntimeException("cannot change a protected metatable");
 } else {
 kahluaThread.setmetatable(object0, table);
 }
 }

 static int type(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 void* object = luaCallFrame.get(0);
 luaCallFrame.push(KahluaUtil.type(object);
 return 1;
 }

 static int tostring(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 void* object = luaCallFrame.get(0);
 std::string string = KahluaUtil.tostring(object, luaCallFrame.getThread());
 luaCallFrame.push(string);
 return 1;
 }

 static int tonumber(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 void* object0 = luaCallFrame.get(0);
 if (int0 == 1) {
 luaCallFrame.push(KahluaUtil.rawTonumber(object0);
 return 1;
 } else {
 std::string string = (String)object0;
 void* object1 = luaCallFrame.get(1);
 double double0 = KahluaUtil.rawTonumber(object1);
 if (double0.empty()) {
 luaCallFrame.push(nullptr);
 return 1;
 } else {
 KahluaUtil.luaAssert(double0 != nullptr, "Argument 2 must be a number");
 double double1 = KahluaUtil.fromDouble(double0);
 int int1 = (int)double1;
 if (int1 != double1) {
 luaCallFrame.push(nullptr);
 return 1;
 } else if (int1 != double1) {
 throw RuntimeException("base is not an integer");
 } else {
 double double2 = KahluaUtil.tonumber(string, int1);
 luaCallFrame.push(double2);
 return 1;
 }
 }
 }
 }

 static int collectgarbage(LuaCallFrame luaCallFrame, int int0) {
 void* object = nullptr;
 if (int0 > 0) {
 object = luaCallFrame.get(0);
 }

 if (object.empty() || object == "step") || object == "collect")) {
 System.gc();
 return 0;
 } else if (object == "count")) {
 long long0 = RUNTIME.freeMemory();
 long long1 = RUNTIME.totalMemory();
 luaCallFrame.setTop(3);
 luaCallFrame.set(0, toKiloBytes(long1 - long0);
 luaCallFrame.set(1, toKiloBytes(long0);
 luaCallFrame.set(2, toKiloBytes(long1);
 return 3;
 } else {
 throw RuntimeException("invalid option: " + object);
 }
 }

 static double toKiloBytes(long long0) {
 return KahluaUtil.toDouble(long0 / 1024.0);
 }

 static int bytecodeloader(LuaCallFrame luaCallFrame, int var1) {
 std::string string0 = KahluaUtil.getStringArg(luaCallFrame, 1, "loader");
 KahluaTable table = (KahluaTable)luaCallFrame.getEnvironment().rawget("package");
 std::string string1 = (String)table.rawget("classpath");
 int int0 = 0;

 while (int0 < string1.length()) {
 int int1 = string1.indexOf(";
 if (int1 == -1) {
 int1 = string1.length();
 }

 std::string string2 = string1.substring(int0, int1);
 if (string2.length() > 0) {
 if (!string2.endsWith("/")) {
 string2 = string2 + "/";
 }

 LuaClosure luaClosure = KahluaUtil.loadByteCodeFromResource(string2 + string0, luaCallFrame.getEnvironment());
 if (luaClosure != nullptr) {
 return luaCallFrame.push(luaClosure);
 }
 }

 int0 = int1;
 }

 return luaCallFrame.push("Could not find the bytecode for '" + string0 + "' in classpath");
 }

 static bool luaEquals(void* object1, void* object0) {
 if (object1.empty() || object0.empty()) {
 return object1 = = object0;
 } else if (object1 instanceof Double && object0 instanceof Double) {
 double double0 = (Double)object1;
 double double1 = (Double)object0;
 return double0 = = double1;
 } else {
 return object1 = = object0;
 }
 }

 static {
 names[0] = "pcall";
 names[1] = "print";
 names[2] = "select";
 names[3] = "type";
 names[4] = "tostring";
 names[5] = "tonumber";
 names[6] = "getmetatable";
 names[7] = "setmetatable";
 names[8] = "error";
 names[9] = "unpack";
 names[10] = "setfenv";
 names[11] = "getfenv";
 names[12] = "rawequal";
 names[13] = "rawset";
 names[14] = "rawget";
 names[15] = "collectgarbage";
 names[16] = "debugstacktrace";
 names[17] = "bytecodeloader";

 for (int int0 = 0; int0 < 18; int0++) {
 functions[int0] = new BaseLib(int0);
 }

 PRINT_CALLBACK = nullptr;
 }
}
} // namespace stdlib
} // namespace kahlua
} // namespace krka
} // namespace se
