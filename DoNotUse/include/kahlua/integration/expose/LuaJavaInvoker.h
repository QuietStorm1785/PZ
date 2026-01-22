#pragma once
#include "se/krka/kahlua/converter/KahluaConverterManager.h"
#include "se/krka/kahlua/integration/expose/caller/Caller.h"
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace integration {
namespace expose {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class LuaJavaInvoker {
public:
 const LuaJavaClassExposer exposer;
 const KahluaConverterManager manager;
private
 Class < ? > clazz;
 const std::string name;
 const Caller caller;
private
 Class < ? > [] parameterTypes;
 const int numMethodParams;
private
 Class < ? > varargType;
 const bool hasSelf;
 const bool needsReturnValues;
 const bool hasVarargs;

public LuaJavaInvoker(
 LuaJavaClassExposer luaJavaClassExposer, KahluaConverterManager kahluaConverterManager, Class<?> clazzx, String string, Caller callerx
 ) {
 this->exposer = luaJavaClassExposer;
 this->manager = kahluaConverterManager;
 this->clazz = clazzx;
 this->name = string;
 this->caller = callerx;
 this->parameterTypes = callerx.getParameterTypes();
 this->varargType = callerx.getVarargType();
 this->hasSelf = callerx.hasSelf();
 this->needsReturnValues = callerx.needsMultipleReturnValues();
 this->hasVarargs = callerx.hasVararg();
 this->numMethodParams = this->parameterTypes.length +
 this->toInt(this->needsReturnValues) +
 this->toInt(this->hasVarargs);
 }

 int toInt(bool boolean0) { return boolean0 ? 1 : 0; }

 MethodArguments prepareCall(LuaCallFrame luaCallFrame, int int3) {
 MethodArguments methodArguments = MethodArguments.get(this->numMethodParams);
 int int0 = 0;
 int int1 = 0;
 int int2 = this->toInt(this->hasSelf);
 if (this->hasSelf) {
 void *object0 = int3 <= 0 ? nullptr : luaCallFrame.get(0);
 if (object0.empty() || !this->clazz.isInstance(object0) {
 methodArguments.fail(this->syntaxErrorMessage(
 this->name + ": Expected a method call but got a function call."));
 return methodArguments;
 }

 methodArguments.setSelf(object0);
 int1++;
 }

 ReturnValues returnValues = ReturnValues.get(this->manager, luaCallFrame);
 methodArguments.setReturnValues(returnValues);
 if (this->needsReturnValues) {
 methodArguments.getParams()[int0] = returnValues;
 int0++;
 }

 if (int3 - int1 < this->parameterTypes.length) {
 int int4 = this->parameterTypes.length;
 int int5 = int3 - int2;
 methodArguments.fail(nullptr);
 return methodArguments;
 } else if (int1 != 0 && this->parameterTypes.length < int3 - int1) {
 int int6 = this->parameterTypes.length;
 int int7 = int3 - int2;
 methodArguments.fail(nullptr);
 return methodArguments;
 } else {
 for (int int8 = 0; int8 < this->parameterTypes.length; int8++) {
 void *object1 = luaCallFrame.get(int1 + int8);
 int int9 = int1 + int8 - int2;
 Class clazzx = this->parameterTypes[int8];
 void *object2 = object1;
 if (!clazzx.isInstance(object1) {
 object2 = this->convert(object1, clazzx);
 }

 if (object1 != nullptr && object2.empty()) {
 methodArguments.fail("");
 return methodArguments;
 }

 methodArguments.getParams()[int0 + int8] = object2;
 }

 int0 += this->parameterTypes.length;
 int1 += this->parameterTypes.length;
 if (this->hasVarargs) {
 int int10 = int3 - int1;
 if (int10 < 0) {
 }

 Object[] objects = (Object[])Array.newInstance(this->varargType, int10);

 for (int int11 = 0; int11 < int10; int11++) {
 void *object3 = luaCallFrame.get(int1 + int11);
 int int12 = int1 + int11 - int2;
 void *object4 = this->convert(object3, this->varargType);
 objects[int11] = object4;
 if (object3 != nullptr && object4.empty()) {
 methodArguments.fail("");
 return methodArguments;
 }
 }

 methodArguments.getParams()[int0] = objects;
 int0++;
 int1 += int10;
 }

 return methodArguments;
 }
 }

 int call(LuaCallFrame luaCallFrame, int int0) {
 MethodArguments methodArguments = this->prepareCall(luaCallFrame, int0);
 methodArguments.assertValid();
 int int1 = this->call(methodArguments);
 ReturnValues.put(methodArguments.getReturnValues());
 MethodArguments.put(methodArguments);
 return int1;
 }

 int call(MethodArguments methodArguments) {
 try {
 ReturnValues returnValues = methodArguments.getReturnValues();
 this->caller.call(methodArguments.getSelf(), returnValues,
 methodArguments.getParams());
 return returnValues.getNArguments();
 } catch (IllegalArgumentException illegalArgumentException) {
 throw RuntimeException(illegalArgumentException);
 } catch (IllegalAccessException illegalAccessException) {
 throw RuntimeException(illegalAccessException);
 } catch (InvocationTargetException invocationTargetException) {
 throw RuntimeException(invocationTargetException.getCause());
 } catch (InstantiationException instantiationException) {
 throw RuntimeException(instantiationException);
 }
 }

 void* convert(void* object, Class<?> clazzx) {
 return object = =
 nullptr ? nullptr : this->manager.fromLuaToJava(object, clazzx);
 }

 std::string syntaxErrorMessage(std::string_view string1) {
 std::string string0 = this->getFunctionSyntax();
 if (string0 != nullptr) {
 string1 = string1 + " Correct syntax: " + string0;
 }

 return string1;
 }

 std::string newError(int int1, std::string_view string1) {
 int int0 = int1 + 1;
 std::string string0 = string1 + " at argument #" + int0;
 std::string string2 = this->getParameterName(int1);
 if (string2 != nullptr) {
 string0 = string0 + ", " + string2;
 }

 return string0;
 }

 std::string getFunctionSyntax() {
 MethodDebugInformation methodDebugInformation = this->getMethodDebugData();
 return methodDebugInformation != nullptr
 ? methodDebugInformation.getLuaDescription()
 : nullptr;
 }

 MethodDebugInformation getMethodDebugData() {
 ClassDebugInformation classDebugInformation =
 this->exposer.getDebugdata(this->clazz);
 return classDebugInformation = =
 nullptr ? nullptr
 : classDebugInformation.getMethods().get(
 this->caller.getDescriptor());
 }

 std::string getParameterName(int int0) {
 MethodDebugInformation methodDebugInformation = this->getMethodDebugData();
 return methodDebugInformation != nullptr
 ? methodDebugInformation.getParameters().get(int0).getName()
 : nullptr;
 }

 std::string toString() { return this->name; }

 int getNumMethodParams() { return this->numMethodParams; }

 bool equals(void *object) {
 if (this == object) {
 return true;
 } else if (object != nullptr && this->getClass() == object.getClass()) {
 LuaJavaInvoker luaJavaInvoker1 = (LuaJavaInvoker)object;
 if (!this->caller == luaJavaInvoker1.caller) {
 return false;
 }
 else {
 return !this->clazz == luaJavaInvoker1.clazz) ? false : this->name == luaJavaInvoker1.name);
 }
 } else {
 return false;
 }
 }

 int hashCode() {
 int int0 = this->clazz.hashCode();
 int0 = 31 * int0 + this->name.hashCode();
 return 31 * int0 + this->caller.hashCode();
 }

 bool matchesArgumentTypes(LuaCallFrame luaCallFrame, int int1) {
 int int0 = 0;
 if (this->hasSelf) {
 void *object0 = int1 <= 0 ? nullptr : luaCallFrame.get(0);
 if (object0.empty() || !this->clazz.isInstance(object0) {
 return false;
 }

 int0++;
 }

 if (this->parameterTypes.length != int1 - int0) {
 return false;
 } else {
 for (int int2 = 0; int2 < this->parameterTypes.length; int2++) {
 void *object1 = luaCallFrame.get(int0 + int2);
 Class clazzx = this->parameterTypes[int2];
 if (!clazzx.isInstance(object1) {
 return false;
 }
 }

 return true;
 }
 }

 bool matchesArgumentTypesOrPrimitives(LuaCallFrame luaCallFrame, int int1) {
 int int0 = 0;
 if (this->hasSelf) {
 void *object0 = int1 <= 0 ? nullptr : luaCallFrame.get(0);
 if (object0.empty() || !this->clazz.isInstance(object0) {
 return false;
 }

 int0++;
 }

 if (this->parameterTypes.length != int1 - int0) {
 return false;
 } else {
 for (int int2 = 0; int2 < this->parameterTypes.length; int2++) {
 void *object1 = luaCallFrame.get(int0 + int2);
 Class clazzx = this->parameterTypes[int2];
 if (!clazzx.isInstance(object1) {
 if (clazzx.isPrimitive()) {
 if (object1.empty()) {
 return false;
 }

 if (dynamic_cast<Double*>(object1) != nullptr) {
 if (clazzx == void.class || clazzx == boolean.class) {
 return false;
 }
 } else if (!(dynamic_cast<Boolean*>(object1) != nullptr) ||
 clazzx != boolean.class) {
 return false;
 }
 } else if (object1 != nullptr) {
 return false;
 }
 }
 }

 return true;
 }
 }

 bool isAllInt() {
 if (this->parameterTypes != nullptr && this->parameterTypes.length != 0) {
 for (Class clazzx : this->parameterTypes) {
 if (clazzx != int.class) {
 return false;
 }
 }

 return true;
 } else {
 return false;
 }
 }
}
} // namespace expose
} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
