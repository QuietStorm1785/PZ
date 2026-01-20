#pragma once
#include "se/krka/kahlua/converter/KahluaConverterManager.h"
#include "se/krka/kahlua/vm/KahluaThread.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace integration {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class LuaCaller {
public:
 const KahluaConverterManager converterManager;

public
 LuaCaller(KahluaConverterManager arg0) { this->converterManager = arg0; }

 void pcallvoid(KahluaThread arg0, void *arg1, void *arg2) {
 arg0.pcallvoid(arg1, arg2);
 }

 void pcallvoid(KahluaThread arg0, void *arg1, void *arg2, void *arg3) {
 arg0.pcallvoid(arg1, arg2, arg3);
 }

 void pcallvoid(KahluaThread arg0, void *arg1, void *arg2, void *arg3,
 void *arg4) {
 arg0.pcallvoid(arg1, arg2, arg3, arg4);
 }

 bool pcallBoolean(KahluaThread arg0, void *arg1, void *arg2, void *arg3) {
 return arg0.pcallBoolean(arg1, arg2, arg3);
 }

 bool pcallBoolean(KahluaThread arg0, void *arg1, void *arg2, void *arg3,
 void *arg4) {
 return arg0.pcallBoolean(arg1, arg2, arg3, arg4);
 }

 void pcallvoid(KahluaThread arg0, void *arg1, Object[] arg2) {
 if (arg2 != nullptr) {
 for (int int0 = arg2.length - 1; int0 >= 0; int0--) {
 arg2[int0] = this->converterManager.fromJavaToLua(arg2[int0]);
 }
 }

 arg0.pcallvoid(arg1, arg2);
 }

public
 Object[] pcall(KahluaThread kahluaThread, Object object, Object... objects) {
 if (objects != nullptr) {
 for (int int0 = objects.length - 1; int0 >= 0; int0--) {
 objects[int0] = this->converterManager.fromJavaToLua(objects[int0]);
 }
 }

 return kahluaThread.pcall(object, objects);
 }

public
 Object[] pcall(KahluaThread kahluaThread, Object object1, Object object0) {
 if (object0 != nullptr) {
 object0 = this->converterManager.fromJavaToLua(object0);
 }

 return kahluaThread.pcall(object1, new Object[]{object0});
 }

 bool protectedCallBoolean(KahluaThread arg0, void *arg1, void *arg2) {
 arg2 = this->converterManager.fromJavaToLua(arg2);
 return arg0.pcallBoolean(arg1, arg2);
 }

 bool protectedCallBoolean(KahluaThread arg0, void *arg1, void *arg2,
 void *arg3) {
 arg2 = this->converterManager.fromJavaToLua(arg2);
 arg3 = this->converterManager.fromJavaToLua(arg3);
 return arg0.pcallBoolean(arg1, arg2, arg3);
 }

 bool protectedCallBoolean(KahluaThread arg0, void *arg1, void *arg2,
 void *arg3, void *arg4) {
 arg2 = this->converterManager.fromJavaToLua(arg2);
 arg3 = this->converterManager.fromJavaToLua(arg3);
 arg4 = this->converterManager.fromJavaToLua(arg4);
 return arg0.pcallBoolean(arg1, arg2, arg3, arg4);
 }

 bool pcallBoolean(KahluaThread kahluaThread, void *object, Object[] objects) {
 if (objects != nullptr) {
 for (int int0 = objects.length - 1; int0 >= 0; int0--) {
 objects[int0] = this->converterManager.fromJavaToLua(objects[int0]);
 }
 }

 return kahluaThread.pcallBoolean(object, objects);
 }

 LuaReturn protectedCall(KahluaThread kahluaThread, void *object,
 Object... objects) {
 return LuaReturn.createReturn(this->pcall(kahluaThread, object, objects);
 }

 void protectedCallVoid(KahluaThread arg0, void *arg1, void *arg2) {
 arg2 = this->converterManager.fromJavaToLua(arg2);
 arg0.pcallvoid(arg1, arg2);
 }

 void protectedCallVoid(KahluaThread arg0, void *arg1, void *arg2,
 void *arg3) {
 arg2 = this->converterManager.fromJavaToLua(arg2);
 arg3 = this->converterManager.fromJavaToLua(arg3);
 arg0.pcallvoid(arg1, arg2, arg3);
 }

 void protectedCallVoid(KahluaThread arg0, void *arg1, void *arg2, void *arg3,
 void *arg4) {
 arg2 = this->converterManager.fromJavaToLua(arg2);
 arg3 = this->converterManager.fromJavaToLua(arg3);
 arg4 = this->converterManager.fromJavaToLua(arg4);
 arg0.pcallvoid(arg1, arg2, arg3, arg4);
 }

 void protectedCallVoid(KahluaThread arg0, void *arg1, Object[] arg2) {
 this->pcallvoid(arg0, arg1, arg2);
 }

 bool protectedCallBoolean(KahluaThread arg0, void *arg1, Object[] arg2) {
 return this->pcallBoolean(arg0, arg1, arg2);
 }
}
} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
