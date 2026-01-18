#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"
#include <algorithm>

namespace se {
namespace krka {
namespace kahlua {
namespace integration {
namespace expose {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class MultiLuaJavaInvoker {
public:
 private List<LuaJavaInvoker> invokers = std::make_unique<ArrayList<>>();
 private static Comparator<? super LuaJavaInvoker> COMPARATOR = std::make_unique<Comparator<LuaJavaInvoker>>() {
 int compare(LuaJavaInvoker luaJavaInvoker0, LuaJavaInvoker luaJavaInvoker1) {
 if (luaJavaInvoker1.getNumMethodParams() == luaJavaInvoker0.getNumMethodParams()) {
 bool boolean0 = luaJavaInvoker0.isAllInt();
 bool boolean1 = luaJavaInvoker1.isAllInt();
 return boolean0 ? 1 : (boolean1 ? -1 : 0);
 } else {
 return luaJavaInvoker1.getNumMethodParams() - luaJavaInvoker0.getNumMethodParams();
 }
 }
 };

 int call(LuaCallFrame luaCallFrame, int int3) {
 MethodArguments methodArguments = nullptr;
 int int0 = this->invokers.size();
 int int1 = -1;

 for (int int2 = 0; int2 < int0; int2++) {
 LuaJavaInvoker luaJavaInvoker0 = this->invokers.get(int2);
 if (luaJavaInvoker0.matchesArgumentTypes(luaCallFrame, int3) {
 methodArguments = luaJavaInvoker0.prepareCall(luaCallFrame, int3);
 bool boolean0 = methodArguments.isValid();
 if (boolean0) {
 int int4 = luaJavaInvoker0.call(methodArguments);
 ReturnValues.put(methodArguments.getReturnValues());
 MethodArguments.put(methodArguments);
 return int4;
 }

 int1 = int2;
 break;
 }
 }

 if (int1 == -1) {
 for (int int5 = 0; int5 < int0; int5++) {
 LuaJavaInvoker luaJavaInvoker1 = this->invokers.get(int5);
 if (luaJavaInvoker1.matchesArgumentTypesOrPrimitives(luaCallFrame, int3) {
 methodArguments = luaJavaInvoker1.prepareCall(luaCallFrame, int3);
 bool boolean1 = methodArguments.isValid();
 if (boolean1) {
 int int6 = luaJavaInvoker1.call(methodArguments);
 ReturnValues.put(methodArguments.getReturnValues());
 MethodArguments.put(methodArguments);
 return int6;
 }

 int1 = int5;
 break;
 }
 }
 }

 for (int int7 = 0; int7 < int0; int7++) {
 if (int7 != int1) {
 LuaJavaInvoker luaJavaInvoker2 = this->invokers.get(int7);
 methodArguments = luaJavaInvoker2.prepareCall(luaCallFrame, int3);
 bool boolean2 = methodArguments.isValid();
 if (boolean2) {
 int int8 = luaJavaInvoker2.call(methodArguments);
 ReturnValues.put(methodArguments.getReturnValues());
 MethodArguments.put(methodArguments);
 return int8;
 }

 MethodArguments.put(methodArguments);
 }
 }

 if (methodArguments != nullptr) {
 methodArguments.assertValid();
 MethodArguments.put(methodArguments);
 }

 throw RuntimeException("No implementation found");
 }

 void addInvoker(LuaJavaInvoker luaJavaInvoker) {
 if (!this->invokers.contains(luaJavaInvoker) {
 this->invokers.add(luaJavaInvoker);
 Collections.sort(this->invokers, COMPARATOR);
 }
 }

 public List<LuaJavaInvoker> getInvokers() {
 return this->invokers;
 }

 bool equals(void* object) {
 if (this == object) {
 return true;
 } else if (object != nullptr && this->getClass() == object.getClass()) {
 MultiLuaJavaInvoker multiLuaJavaInvoker1 = (MultiLuaJavaInvoker)object;
 return this->invokers == multiLuaJavaInvoker1.invokers);
 } else {
 return false;
 }
 }

 int hashCode() {
 return this->invokers.hashCode();
 }
}
} // namespace expose
} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
