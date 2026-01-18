#pragma once
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/Core.h"
#include "zombie/core/utils/HashMap.h"
#include <cstdint>
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

class LuaCallFrame {
public:
 const Platform platform;
 const Coroutine coroutine;
 LuaClosure closure;
 JavaFunction javaFunction;
 int pc;
 int localBase;
 int returnBase;
 int nArguments;
 bool fromLua;
 bool canYield;
 bool restoreTop;
 int localsAssigned = 0;
 std::unordered_map LocalVarToStackMap = new HashMap();
 std::unordered_map LocalStackToVarMap = new HashMap();
public
 ArrayList<String> LocalVarNames = std::make_unique<ArrayList<>>();

public
 LuaCallFrame(Coroutine arg0) {
 this->coroutine = arg0;
 this->platform = arg0.getPlatform();
 }

 std::string getFilename() {
 return this->closure != nullptr ? this->closure.prototype.filename : nullptr;
 }

 void set(int arg0, void *arg1) {
 this->coroutine.objectStack[this->localBase + arg0] = arg1;
 }

 void *get(int arg0) {
 return this->coroutine.objectStack[this->localBase + arg0];
 }

 int push(void *arg0) {
 int int0 = this->getTop();
 this->setTop(int0 + 1);
 this->set(int0, arg0);
 return 1;
 }

 int push(void *arg0, void *arg1) {
 int int0 = this->getTop();
 this->setTop(int0 + 2);
 this->set(int0, arg0);
 this->set(int0 + 1, arg1);
 return 2;
 }

 int pushNil() { return this->push(nullptr); }

 void stackCopy(int arg0, int arg1, int arg2) {
 this->coroutine.stackCopy(this->localBase + arg0, this->localBase + arg1,
 arg2);
 }

 void stackClear(int arg0, int arg1) {
 while (arg0 <= arg1) {
 this->coroutine.objectStack[this->localBase + arg0] = nullptr;
 arg0++;
 }
 }

 void clearFromIndex(int arg0) {
 if (this->getTop() < arg0) {
 this->setTop(arg0);
 }

 this->stackClear(arg0, this->getTop() - 1);
 }

 void setTop(int arg0) { this->coroutine.setTop(this->localBase + arg0); }

 void closeUpvalues(int arg0) {
 this->coroutine.closeUpvalues(this->localBase + arg0);
 }

 UpValue findUpvalue(int arg0) {
 return this->coroutine.findUpvalue(this->localBase + arg0);
 }

 int getTop() { return this->coroutine.getTop() - this->localBase; }

 void init() {
 if (this->isLua()) {
 this->pc = 0;
 if (this->closure.prototype.isVararg) {
 this->localBase = this->localBase + this->nArguments;
 this->setTop(this->closure.prototype.maxStacksize);
 int int0 = Math.min(this->nArguments, this->closure.prototype.numParams);
 this->stackCopy(-this->nArguments, 0, int0);
 } else {
 this->setTop(this->closure.prototype.maxStacksize);
 this->stackClear(this->closure.prototype.numParams, this->nArguments);
 }
 }
 }

 void setPrototypeStacksize() {
 if (this->isLua()) {
 this->setTop(this->closure.prototype.maxStacksize);
 }
 }

 void pushVarargs(int arg0, int arg1) {
 int int0 = this->closure.prototype.numParams;
 int int1 = this->nArguments - int0;
 if (int1 < 0) {
 int1 = 0;
 }

 if (arg1 == -1) {
 arg1 = int1;
 this->setTop(arg0 + int1);
 }

 if (int1 > arg1) {
 int1 = arg1;
 }

 this->stackCopy(-this->nArguments + int0, arg0, int1);
 int int2 = arg1 - int1;
 if (int2 > 0) {
 this->stackClear(arg0 + int1, arg0 + arg1 - 1);
 }
 }

 KahluaTable getEnvironment() {
 return this->isLua() ? this->closure.env : this->coroutine.environment;
 }

 bool isJava() { return !this->isLua(); }

 bool isLua() { return this->closure != nullptr; }

 std::string toString2() {
 if (this->closure != nullptr) {
 return this->closure.toString2(this->pc);
 } else {
 return this->javaFunction != nullptr
 ? "Callframe at: " + this->javaFunction.toString()
 : super.toString();
 }
 }

 std::string toString() {
 if (this->closure != nullptr) {
 return "Callframe at: " + this->closure.toString();
 } else {
 return this->javaFunction != nullptr
 ? "Callframe at: " + this->javaFunction.toString()
 : super.toString();
 }
 }

 Platform getPlatform() { return this->platform; }

 void setup(LuaClosure luaClosure, JavaFunction javaFunctionx, int int0,
 int int1, int int2, bool boolean0, bool boolean1) {
 this->localBase = int0;
 this->returnBase = int1;
 this->nArguments = int2;
 this->fromLua = boolean0;
 this->canYield = boolean1;
 this->closure = luaClosure;
 this->javaFunction = javaFunctionx;
 LuaCallFrame luaCallFrame1 = this;
 this->localsAssigned = 0;
 this->LocalVarToStackMap.clear();
 this->LocalStackToVarMap.clear();
 this->LocalVarNames.clear();
 if (Core.bDebug && this != nullptr && this->closure != nullptr &&
 this->getThread() == LuaManager.thread) {
 for (int int3 = int0; int3 < int0 + int2; int3++) {
 int int4 = luaCallFrame1.closure.prototype.lines[0];
 if (luaCallFrame1.closure.prototype.locvarlines != nullptr &&
 luaCallFrame1.closure.prototype
 .locvarlines[luaCallFrame1.localsAssigned] < int4 &&
 luaCallFrame1.closure.prototype
 .locvarlines[luaCallFrame1.localsAssigned] != 0) {
 int int5 = luaCallFrame1.localsAssigned++;
 std::string string = luaCallFrame1.closure.prototype.locvars[int5];
 if (string == "group")) {
 bool boolean2 = false;
 }

 luaCallFrame1.setLocalVarToStack(string, int3);
 }
 }
 }
 }

 KahluaThread getThread() { return this->coroutine.getThread(); }

 LuaClosure getClosure() { return this->closure; }

 void setLocalVarToStack(const std::string &arg0, int arg1) {
 this->LocalVarToStackMap.put(arg0, arg1);
 this->LocalStackToVarMap.put(arg1, arg0);
 this->LocalVarNames.add(arg0);
 }

 std::string getNameOfStack(int arg0) {
 return this->LocalStackToVarMap.get(arg0) instanceof
 String ? (String)this->LocalStackToVarMap.get(arg0) : "";
 }

 void printoutLocalVars() {}
}
} // namespace vm
} // namespace kahlua
} // namespace krka
} // namespace se
