#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/luaj/compiler/LuaCompiler.h"
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaUtil.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"
#include "se/krka/kahlua/vm/LuaClosure.h"
#include <fstream>
#include <iostream>

namespace se {
namespace krka {
namespace kahlua {
namespace require {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Require {
public:
 const LuaSourceProvider luaSourceProvider;

 void install(KahluaTable table) {
 table.rawset("require", this);
 table.rawset(this, std::make_unique<HashMap>());
 }

 public Require(LuaSourceProvider luaSourceProviderx) {
 this->luaSourceProvider = luaSourceProviderx;
 }

 int call(LuaCallFrame luaCallFrame, int var2) {
 KahluaTable table = luaCallFrame.getEnvironment();
 std::unordered_map map = (Map)luaCallFrame.getThread().tableget(table, this);
 std::string string0 = KahluaUtil.getStringArg(luaCallFrame, 1, "require");
 Require.Result result = (Require.Result)map.get(string0);
 if (result == nullptr) {
 this->setState(map, string0, Require.Result.LOADING);
 Reader reader = this->luaSourceProvider.getLuaSource(string0);
 if (reader == nullptr) {
 this->error(map, string0, "Does not exist: " + string0);
 }

 try {
 LuaClosure luaClosure = LuaCompiler.loadis(reader, string0, table);
 this->setState(map, string0, Require.Result.LOADING);
 luaCallFrame.getThread().call(luaClosure, nullptr, nullptr, nullptr);
 this->setState(map, string0, Require.Result.LOADED);
 return 0;
 } catch (IOException iOException) {
 this->error(map, string0, "Error in: " + string0 + ": " + iOException.getMessage());
 } catch (RuntimeException runtimeException) {
 std::string string1 = "Error in: " + string0 + ": " + runtimeException.getMessage();
 this->setState(map, string0, Require.Result.error(string1);
 throw RuntimeException(string1, runtimeException);
 }
 }

 if (result == Require.Result.LOADING) {
 this->error(map, string0, "Circular dependency found for: " + string0);
 }

 if (result.state == Require.State.BROKEN) {
 KahluaUtil.fail(result.errorMessage);
 }

 return 0;
 }

 void error(Require.Result> map, const std::string& string0, const std::string& string1) {
 this->setState(map, string0, Require.Result.error(string1);
 KahluaUtil.fail(string1);
 }

 void setState(Require.Result> map, const std::string& string, Require.Result result) {
 map.put(string, result);
 }

 private static class Result {
 const std::string errorMessage;
 public Require.State state;
 public static Require.Result LOADING = new Require.Result(nullptr, Require.State.LOADING);
 public static Require.Result LOADED = new Require.Result(nullptr, Require.State.LOADED);

 private Result(const std::string& string, Require.State statex) {
 this->errorMessage = string;
 this->state = statex;
 }

 public static Require.Result error(String string) {
 return new Require.Result(string, Require.State.BROKEN);
 }
 }

 private static enum State {
 LOADING,
 LOADED,
 BROKEN;
 }
}
} // namespace require
} // namespace kahlua
} // namespace krka
} // namespace se
