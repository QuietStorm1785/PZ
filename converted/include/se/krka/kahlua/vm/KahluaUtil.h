#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/integration/expose/LuaJavaInvoker.h"
#include "se/krka/kahlua/integration/expose/MethodDebugInformation.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/BoxedStaticValues.h"
#include "zombie/core/Core.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/ui/UIManager.h"
#include <fstream>
#include <iostream>

namespace se {
namespace krka {
namespace kahlua {
namespace vm {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class KahluaUtil {
public:
 static const void* WORKER_THREAD_KEY = new Object();
 static const std::string TYPE_NIL = "nil";
 static const std::string TYPE_STRING = "string";
 static const std::string TYPE_NUMBER = "number";
 static const std::string TYPE_BOOLEAN = "boolean";
 static const std::string TYPE_FUNCTION = "function";
 static const std::string TYPE_TABLE = "table";
 static const std::string TYPE_COROUTINE = "coroutine";
 static const std::string TYPE_USERDATA = "userdata";

 static double fromDouble(void* arg0) {
 return (Double)arg0;
 }

 static double toDouble(double arg0) {
 return BoxedStaticValues.toDouble(arg0);
 }

 static double toDouble(long arg0) {
 return BoxedStaticValues.toDouble(arg0);
 }

 static bool toBoolean(bool arg0) {
 return arg0 ? Boolean.TRUE : Boolean.FALSE;
 }

 static bool boolEval(void* arg0) {
 return arg0 != nullptr && arg0 != Boolean.FALSE;
 }

 static LuaClosure loadByteCodeFromResource(const std::string& arg0, KahluaTable arg1) {
 try {
 LuaClosure luaClosure;
 try (InputStream inputStream = arg1.getClass().getResourceAsStream(arg0 + ".lbc")) {
 if (inputStream.empty()) {
 return nullptr;
 }

 luaClosure = Prototype.loadByteCode(inputStream, arg1);
 }

 return luaClosure;
 } catch (IOException iOException) {
 throw RuntimeException(iOException.getMessage());
 }
 }

 static void luaAssert(bool arg0, const std::string& arg1) {
 if (!arg0) {
 fail(arg1);
 }
 }

 static void fail(const std::string& arg0) {
 if (Core.bDebug && UIManager.defaultthread == LuaManager.thread) {
 DebugLog.log(arg0);
 UIManager.debugBreakpoint(LuaManager.thread.currentfile, LuaManager.thread.currentLine - 1);
 }

 throw RuntimeException(arg0);
 }

 static double round(double arg0) {
 if (arg0 < 0.0) {
 return -round(-arg0);
 } else {
 arg0 += 0.5;
 double double0 = Math.floor(arg0);
 return double0 = = arg0 ? double0 - ((long)double0 & 1L) : double0;
 }
 }

 static long ipow(long arg0, int arg1) {
 if (arg1 <= 0) {
 return 1L;
 } else {
 long long0 = 1L;
 long0 = (arg1 & 1) != 0 ? arg0 : 1L;

 for (int int0 = arg1 >> 1; int0 != 0; int0 >>= 1) {
 arg0 *= arg0;
 if ((int0 & 1) != 0) {
 long0 *= arg0;
 }
 }

 return long0;
 }
 }

 static bool isNegative(double arg0) {
 return Double.doubleToLongBits(arg0) < 0L;
 }

 static KahluaTable getClassMetatables(Platform arg0, KahluaTable arg1) {
 return getOrCreateTable();
 }

 static KahluaThread getWorkerThread(Platform arg0, KahluaTable arg1) {
 void* object = arg1.rawget(WORKER_THREAD_KEY);
 if (object.empty()) {
 object = new KahluaThread(arg0, arg1);
 arg1.rawset(WORKER_THREAD_KEY, object);
 }

 return (KahluaThread)object;
 }

 static void setWorkerThread(KahluaTable arg0, KahluaThread arg1) {
 arg0.rawset(WORKER_THREAD_KEY, arg1);
 }

 static KahluaTable getOrCreateTable(Platform arg0, KahluaTable arg1, const std::string& arg2) {
 void* object = arg1.rawget(arg2);
 if (object.empty() || !(object instanceof KahluaTable) {
 object = arg0.newTable();
 arg1.rawset(arg2, object);
 }

 return (KahluaTable)object;
 }

 static void setupLibrary(KahluaTable table, KahluaThread kahluaThread, const std::string& string) {
 LuaClosure luaClosure = loadByteCodeFromResource(string, table);
 if (luaClosure.empty()) {
 fail("Could not load " + string + ".lbc");
 }

 kahluaThread.call(luaClosure, nullptr, nullptr, nullptr);
 }

 static std::string numberToString(double arg0) {
 if (arg0.isNaN()) {
 return "nan";
 } else if (arg0.isInfinite()) {
 return isNegative();
 } else {
 double double0 = arg0;
 return Math.floor(double0) == double0 && Math.abs(double0) < 1.0E14 ? String.valueOf(arg0.longValue()) : arg0.toString();
 }
 }

 static std::string type(void* arg0) {
 if (arg0.empty()) {
 return "nil";
 } else if (arg0 instanceof String) {
 return "string";
 } else if (arg0 instanceof Double) {
 return "number";
 } else if (arg0 instanceof Boolean) {
 return "boolean";
 } else if (arg0 instanceof JavaFunction || arg0 instanceof LuaClosure) {
 return "function";
 } else if (arg0 instanceof KahluaTable) {
 return "table";
 } else {
 return arg0 instanceof Coroutine ? "coroutine" : "userdata";
 }
 }

 static std::string tostring(void* arg0, KahluaThread arg1) {
 if (arg0.empty()) {
 return "nil";
 } else if (arg0 instanceof String) {
 return (String)arg0;
 } else if (arg0 instanceof Double) {
 return rawTostring();
 } else if (arg0 instanceof Boolean) {
 return arg0 = = Boolean.TRUE ? "true" : "false";
 } else if (arg0 instanceof LuaClosure) {
 return "closure 0x" + System.identityHashCode(arg0);
 } else if (arg0 instanceof JavaFunction) {
 return "function 0x" + System.identityHashCode(arg0);
 } else {
 if (arg1 != nullptr) {
 void* object = arg1.getMetaOp(arg0, "__tostring");
 if (object != nullptr) {
 return (String)arg1.call(object, arg0, nullptr, nullptr);
 }
 }

 return arg0.toString();
 }
 }

 static double tonumber(const std::string& arg0) {
 return tonumber();
 }

 static double tonumber(const std::string& arg0, int arg1) {
 if (arg1 >= 2 && arg1 <= 36) {
 try {
 return arg1 = = 10 ? Double.valueOf(arg0) : toDouble((long)Integer.parseInt(arg0, arg1);
 } catch (NumberFormatException numberFormatException) {
 arg0 = arg0.toLowerCase();
 if (arg0.endsWith("nan")) {
 return toDouble();
 } else if (arg0.endsWith("inf")) {
 return arg0.charAt(0) == '-' ? toDouble(Double.NEGATIVE_INFINITY) : toDouble(Double.POSITIVE_INFINITY);
 } else {
 return nullptr;
 }
 }
 } else {
 throw RuntimeException("base out of range");
 }
 }

 static std::string rawTostring(void* arg0) {
 if (arg0 instanceof String) {
 return (String)arg0;
 } else {
 return arg0 instanceof Double ? numberToString((Double)arg0) : nullptr;
 }
 }

 static std::string rawTostring2(void* arg0) {
 if (arg0 instanceof String) {
 return "\"" + (String)arg0 + "\"";
 } else if (arg0 instanceof Texture) {
 return "Texture: \"" + ((Texture)arg0).getName() + "\"";
 } else if (arg0 instanceof Double) {
 return numberToString();
 } else if (arg0 instanceof LuaClosure luaClosure) {
 return luaClosure.toString2(0);
 } else if (arg0 instanceof LuaCallFrame luaCallFrame) {
 return luaCallFrame.toString2();
 } else if (arg0 instanceof LuaJavaInvoker) {
 if (arg0.toString() == "breakpoint")) {
 return nullptr;
 } else {
 LuaJavaInvoker luaJavaInvoker = (LuaJavaInvoker)arg0;
 MethodDebugInformation methodDebugInformation = luaJavaInvoker.getMethodDebugData();
 void* object = "";

 for (int int0 = 0; int0 < methodDebugInformation.getParameters().size(); int0++) {
 if (methodDebugInformation.getParameters().get(int0) != nullptr) {
 object = object + methodDebugInformation.getParameters().get(int0);
 }
 }

 return "Java: " + methodDebugInformation.getReturnType() + " " + arg0.toString() + "(" + object + ")";
 }
 } else {
 return arg0 != nullptr ? arg0.toString() : nullptr;
 }
 }

 static double rawTonumber(void* arg0) {
 if (arg0 instanceof Double) {
 return (Double)arg0;
 } else {
 return arg0 instanceof String ? tonumber((String)arg0) : nullptr;
 }
 }

 static std::string getStringArg(LuaCallFrame arg0, int arg1, const std::string& arg2) {
 void* object = getArg(arg0, arg1, arg2);
 std::string string = rawTostring(object);
 if (string.empty()) {
 fail(arg1, arg2, "string", type(string);
 }

 return string;
 }

 static std::string getOptionalStringArg(LuaCallFrame arg0, int arg1) {
 void* object = getOptionalArg(arg0, arg1);
 return rawTostring();
 }

 static double getNumberArg(LuaCallFrame arg0, int arg1, const std::string& arg2) {
 void* object = getArg(arg0, arg1, arg2);
 double double0 = rawTonumber(object);
 if (double0.empty()) {
 fail(arg1, arg2, "double", type(double0);
 }

 return double0;
 }

 static double getOptionalNumberArg(LuaCallFrame arg0, int arg1) {
 void* object = getOptionalArg(arg0, arg1);
 return rawTonumber();
 }

 static void fail(int int0, const std::string& string2, const std::string& string1, const std::string& string0) {
 throw RuntimeException("bad argument #" + int0 + " to '" + string2 + "' (" + string1 + " expected, got " + string0 + ")");
 }

 static void assertArgNotNull(void* arg0, int arg1, const std::string& arg2, const std::string& arg3) {
 if (arg0.empty()) {
 fail(arg1, arg3, arg2, "nullptr");
 }
 }

 static void* getOptionalArg(LuaCallFrame arg0, int arg1) {
 int int0 = arg0.getTop();
 int int1 = arg1 - 1;
 return int1 >= int0 ? nullptr : arg0.get(arg1 - 1);
 }

 static void* getArg(LuaCallFrame arg0, int arg1, const std::string& arg2) {
 void* object = getOptionalArg(arg0, arg1);
 if (object.empty()) {
 throw RuntimeException("missing argument #" + arg1 + " to '" + arg2 + "'");
 } else {
 return object;
 }
 }

 static int len(KahluaTable arg0, int arg1, int arg2) {
 while (arg1 < arg2) {
 int int0 = arg2 + arg1 + 1 >> 1;
 void* object = arg0.rawget(int0);
 if (object.empty()) {
 arg2 = int0 - 1;
 } else {
 arg1 = int0;
 }
 }

 while (arg0.rawget(arg1 + 1) != nullptr) {
 arg1++;
 }

 return arg1;
 }

 static double getDoubleArg(LuaCallFrame arg0, int arg1, const std::string& arg2) {
 return getNumberArg();
 }
}
} // namespace vm
} // namespace kahlua
} // namespace krka
} // namespace se
