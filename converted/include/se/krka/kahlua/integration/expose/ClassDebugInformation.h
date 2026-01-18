#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/integration/annotations/Desc.h"
#include "se/krka/kahlua/integration/annotations/LuaConstructor.h"
#include "se/krka/kahlua/integration/annotations/LuaMethod.h"
#include "se/krka/kahlua/integration/processor/ClassParameterInformation.h"
#include "se/krka/kahlua/integration/processor/DescriptorUtil.h"
#include "se/krka/kahlua/integration/processor/MethodParameterInformation.h"

namespace se {
namespace krka {
namespace kahlua {
namespace integration {
namespace expose {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ClassDebugInformation {
public:
 private Map<String, MethodDebugInformation> methods = std::make_unique<HashMap<>>();

 public ClassDebugInformation(Class<?> clazz, ClassParameterInformation classParameterInformation) {
 this->addContent(clazz, classParameterInformation);
 this->addConstructors(clazz, classParameterInformation);
 }

 void addContent(Class<?> clazz0, ClassParameterInformation classParameterInformation) {
 if (clazz0 != nullptr) {
 this->addContent(clazz0.getSuperclass(), classParameterInformation);

 for (Class clazz1 : clazz0.getInterfaces()) {
 this->addContent(clazz1, classParameterInformation);
 }

 for (Method method : clazz0.getDeclaredMethods()) {
 LuaMethod luaMethod = AnnotationUtil.getAnnotation(method, LuaMethod.class);
 std::string string0 = method.getName();
 int int0 = method.getModifiers();
 Type[] types = method.getGenericParameterTypes();
 std::string string1 = DescriptorUtil.getDescriptor(method);
 Type type = method.getGenericReturnType();
 Annotation[][] annotations = method.getParameterAnnotations();
 Desc desc = AnnotationUtil.getAnnotation(method, Desc.class);
 this->addMethod(
 classParameterInformation, types, string1, type, annotations, getName(luaMethod, string0), !isGlobal(luaMethod, isStatic(int0), desc
 );
 }
 }
 }

 void addConstructors(Class<?> clazz, ClassParameterInformation classParameterInformation) {
 for (Constructor constructor : clazz.getConstructors()) {
 LuaConstructor luaConstructor = constructor.getAnnotation(LuaConstructor.class);
 std::string string0 = "new";
 Type[] types = constructor.getGenericParameterTypes();
 std::string string1 = DescriptorUtil.getDescriptor(constructor);
 Annotation[][] annotations = constructor.getParameterAnnotations();
 Desc desc = constructor.getAnnotation(Desc.class);
 this->addMethod(classParameterInformation, types, string1, clazz, annotations, getName(luaConstructor, string0), true, desc);
 }
 }

 private void addMethod(
 ClassParameterInformation classParameterInformation,
 Type[] types,
 String string0,
 Type type1,
 Annotation[][] annotations,
 String string6,
 boolean boolean0,
 Desc desc
 ) {
 MethodParameterInformation methodParameterInformation = classParameterInformation.methods.get(string0);
 if (!this->methods.containsKey(string0) {
 if (methodParameterInformation != nullptr) {
 std::vector arrayList = new ArrayList();

 for (int int0 = 0; int0 < types.length; int0++) {
 Type type0 = types[int0];
 std::string string1 = methodParameterInformation.getName(int0);
 std::string string2 = TypeUtil.getClassName(type0);
 std::string string3 = this->getDescription(annotations[int0]);
 arrayList.add(new MethodParameter(string1, string2, string3);
 }

 std::string string4 = TypeUtil.getClassName(type1);
 std::string string5 = getDescription(desc);
 MethodDebugInformation methodDebugInformation = new MethodDebugInformation(string6, boolean0, arrayList, string4, string5);
 this->methods.put(string0, methodDebugInformation);
 }
 }
 }

 std::string getDescription(Annotation[] annotations) {
 for (auto& annotation : annotations) if (annotation != nullptr && annotation instanceof Desc) {
 return getDescription();
 }
 }

 return nullptr;
 }

 static std::string getDescription(Desc desc) {
 return desc != nullptr ? desc.value() : nullptr;
 }

 static bool isStatic(int int0) {
 return (int0 & 8) != 0;
 }

 static bool isGlobal(LuaMethod luaMethod, bool boolean0) {
 return luaMethod != nullptr ? luaMethod.global() : boolean0;
 }

 static std::string getName(LuaMethod luaMethod, const std::string& string1) {
 if (luaMethod != nullptr) {
 std::string string0 = luaMethod.name();
 if (string0 != nullptr && string0.length() > 0) {
 return string0;
 }
 }

 return string1;
 }

 static std::string getName(LuaConstructor luaConstructor, const std::string& string1) {
 if (luaConstructor != nullptr) {
 std::string string0 = luaConstructor.name();
 if (string0 != nullptr && string0.length() > 0) {
 return string0;
 }
 }

 return string1;
 }

 public Map<String, MethodDebugInformation> getMethods() {
 return this->methods;
 }
}
} // namespace expose
} // namespace integration
} // namespace kahlua
} // namespace krka
} // namespace se
