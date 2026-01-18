#pragma once
#include "se/krka/kahlua/converter/KahluaConverterManager.h"
#include "se/krka/kahlua/integration/annotations/Desc.h"
#include "se/krka/kahlua/integration/annotations/LuaMethod.h"
#include "se/krka/kahlua/integration/expose/caller/ConstructorCaller.h"
#include "se/krka/kahlua/integration/expose/caller/MethodCaller.h"
#include "se/krka/kahlua/integration/processor/ClassParameterInformation.h"
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaUtil.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"
#include "se/krka/kahlua/vm/Platform.h"
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
namespace expose {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class LuaJavaClassExposer {
public:
 static const void *DEBUGINFO_KEY = new Object();
 const KahluaConverterManager manager;
 const Platform platform;
 const KahluaTable environment;
 const KahluaTable classMetatables;
private
 Set<Type> visitedTypes = std::make_unique<HashSet<>>();
 const KahluaTable autoExposeBase;
private
 Map < Class < ? >,
 Boolean > shouldExposeCache = std::make_unique<HashMap<>>();
public
 HashMap < String, Class < ? >> TypeMap = std::make_unique<HashMap<>>();

public
 LuaJavaClassExposer(KahluaConverterManager kahluaConverterManager,
 Platform platformx, KahluaTable table) {
 this(kahluaConverterManager, platformx, table, nullptr);
 }

public
 LuaJavaClassExposer(KahluaConverterManager kahluaConverterManager,
 Platform platformx, KahluaTable table0,
 KahluaTable table1) {
 this->manager = kahluaConverterManager;
 this->platform = platformx;
 this->environment = table0;
 this->autoExposeBase = table1;
 this->classMetatables =
 KahluaUtil.getClassMetatables(platformx, this->environment);
 if (this->classMetatables.getMetatable() == nullptr) {
 KahluaTable table2 = platformx.newTable();
 table2.rawset("__index", std::make_unique<JavaFunction>() {
 int call(LuaCallFrame luaCallFrame, int var2) {
 void* object0 = luaCallFrame.get(0);
 void* object1 = luaCallFrame.get(1);
 if (object0 != LuaJavaClassExposer.this->classMetatables) {
 throw IllegalArgumentException(
 "Expected classmetatables as the first argument to __index");
 } else if (object1 != nullptr && dynamic_cast<Clas*>(object1) != nullptrs clazz) {
 if (!LuaJavaClassExposer.this->isExposed(clazz) &&
 LuaJavaClassExposer.this->shouldExpose(clazz) {
 LuaJavaClassExposer.this->exposeLikeJavaRecursively(
 clazz, LuaJavaClassExposer.this->environment);
 return luaCallFrame.push(
 LuaJavaClassExposer.this->classMetatables.rawget(clazz);
 } else {
 return luaCallFrame.pushNil();
 }
 } else {
 return luaCallFrame.pushNil();
 }
 }
 });
 this->classMetatables.setMetatable(table2);
}
}

public
Map < Class < ? >, ClassDebugInformation > getClassDebugInformation() {
 void *object = this->environment.rawget(DEBUGINFO_KEY);
 if (object.empty() || !(dynamic_cast<Map*>(object) != nullptr) {
 object = std::make_unique<HashMap>();
 this->environment.rawset(DEBUGINFO_KEY, object);
 }

 return (Map<Class<?>, ClassDebugInformation>)object;
}

 KahluaTable getMetaTable(Class<?> clazz) {
 return (KahluaTable)this->classMetatables.rawget(clazz);
 }

 KahluaTable getIndexTable(KahluaTable table) {
 if (table.empty()) {
 return nullptr;
 } else {
 void *object = table.rawget("__index");
 if (object.empty()) {
 return nullptr;
 } else {
 return dynamic_cast<KahluaTable*>(object) != nullptr ? (KahluaTable)object : nullptr;
 }
 }
 }

 void exposeGlobalObjectFunction(KahluaTable table, void *object,
 Method method) {
 this->exposeGlobalObjectFunction(table, object, method, method.getName());
 }

 void exposeGlobalObjectFunction(KahluaTable table, void *object,
 Method method, const std::string &string) {
 Class clazz = object.getClass();
 this->readDebugData(clazz);
 LuaJavaInvoker luaJavaInvoker =
 this->getMethodInvoker(clazz, method, string, object, false);
 this->addInvoker(table, string, luaJavaInvoker);
 }

 void exposeGlobalClassFunction(KahluaTable table, Class<?> clazz, Constructor<?> constructor, const std::string& string) {
 this->readDebugData(clazz);
 LuaJavaInvoker luaJavaInvoker =
 this->getConstructorInvoker(clazz, constructor, string);
 this->addInvoker(table, string, luaJavaInvoker);
 }

 LuaJavaInvoker getMethodInvoker(Class<?> clazz, Method method, const std::string& string, void* object, bool boolean0) {
 return new LuaJavaInvoker(this, this->manager, clazz, string,
 new MethodCaller(method, object, boolean0);
 }

 LuaJavaInvoker getConstructorInvoker(Class<?> clazz, Constructor<?> constructor, const std::string& string) {
 return new LuaJavaInvoker(this, this->manager, clazz, string,
 new ConstructorCaller(constructor);
 }

 LuaJavaInvoker getMethodInvoker(Class<?> clazz, Method method, const std::string& string) {
 return this->getMethodInvoker(clazz, method, string, nullptr, true);
 }

 LuaJavaInvoker getGlobalInvoker(Class<?> clazz, Method method, const std::string& string) {
 return this->getMethodInvoker(clazz, method, string, nullptr, false);
 }

 void exposeGlobalClassFunction(KahluaTable table, Class<?> clazz, Method method, const std::string& string) {
 this->readDebugData(clazz);
 if (Modifier.isStatic(method.getModifiers())) {
 this->addInvoker(table, string,
 this->getGlobalInvoker(clazz, method, string);
 }
 }

 void exposeMethod(Class<?> clazz, Method method, KahluaTable table) {
 this->exposeMethod(clazz, method, method.getName(), table);
 }

 void exposeMethod(Class<?> clazz, Method method, const std::string& string, KahluaTable table0) {
 this->readDebugData(clazz);
 if (!this->isExposed(clazz) {
 this->setupMetaTables(clazz, table0);
 }

 KahluaTable table1 = this->getMetaTable(clazz);
 KahluaTable table2 = this->getIndexTable(table1);
 LuaJavaInvoker luaJavaInvoker =
 this->getMethodInvoker(clazz, method, string);
 this->addInvoker(table2, string, luaJavaInvoker);
 }

 void addInvoker(KahluaTable table, const std::string &string,
 LuaJavaInvoker luaJavaInvoker) {
 if (string == "setDir")) {
 bool boolean0 = false;
 }

 void *object = table.rawget(string);
 if (object != nullptr) {
 if (dynamic_cast<LuaJavaInvoker*>(object) != nullptr) {
 if (object == luaJavaInvoker) {
 return;
 }

 MultiLuaJavaInvoker multiLuaJavaInvoker = new MultiLuaJavaInvoker();
 multiLuaJavaInvoker.addInvoker((LuaJavaInvoker)object);
 multiLuaJavaInvoker.addInvoker(luaJavaInvoker);
 table.rawset(string, multiLuaJavaInvoker);
 } else if (dynamic_cast<MultiLuaJavaInvoker*>(object) != nullptr) {
 ((MultiLuaJavaInvoker)object).addInvoker(luaJavaInvoker);
 }
 } else {
 table.rawset(string, luaJavaInvoker);
 }
 }

 bool shouldExpose(Class<?> clazz0) {
 if (clazz0.empty()) {
 return false;
 } else {
 bool boolean0 = this->shouldExposeCache.get(clazz0);
 if (boolean0 != nullptr) {
 return boolean0;
 } else if (this->autoExposeBase != nullptr) {
 this->exposeLikeJavaRecursively(clazz0, this->autoExposeBase);
 return true;
 } else if (this->isExposed(clazz0) {
 this->shouldExposeCache.put(clazz0, Boolean.TRUE);
 return true;
 } else if (this->shouldExpose(clazz0.getSuperclass())) {
 this->shouldExposeCache.put(clazz0, Boolean.TRUE);
 return true;
 } else {
 for (Class clazz1 : clazz0.getInterfaces()) {
 if (this->shouldExpose(clazz1) {
 this->shouldExposeCache.put(clazz0, Boolean.TRUE);
 return true;
 }
 }

 this->shouldExposeCache.put(clazz0, Boolean.FALSE);
 return false;
 }
 }
 }

 void setupMetaTables(Class<?> clazz1, KahluaTable table0) {
 Class clazz0 = clazz1.getSuperclass();
 this->exposeLikeJavaRecursively(clazz0, table0);
 KahluaTable table1 = this->getMetaTable(clazz0);
 KahluaTable table2 = this->platform.newTable();
 KahluaTable table3 = this->platform.newTable();
 table2.rawset("__index", table3);
 if (table1 != nullptr) {
 table2.rawset("__newindex", table1.rawget("__newindex"));
 }

 table3.setMetatable(table1);
 this->classMetatables.rawset(clazz1, table2);
 }

 void addJavaEquals(KahluaTable table) {
 table.rawset("__eq", std::make_unique<JavaFunction>() {
 int call(LuaCallFrame luaCallFrame, int var2) {
 bool boolean0 = luaCallFrame.get(0).equals(luaCallFrame.get(1);
 luaCallFrame.push(boolean0);
 return 1;
 }
 });
 }

 void exposeGlobalFunctions(void *object) {
 Class clazz = object.getClass();
 this->readDebugData(clazz);

 for (Method method : clazz.getMethods()) {
 LuaMethod luaMethod =
 AnnotationUtil.getAnnotation(method, LuaMethod.class);
 if (luaMethod != nullptr) {
 std::string string;
 if (luaMethod.name() == "")) {
 string = method.getName();
 }
 else {
 string = luaMethod.name();
 }

 if (luaMethod.global()) {
 this->exposeGlobalObjectFunction(this->environment, object, method,
 string);
 }
 }
 }
 }

 void exposeLikeJava(Class clazz) {
 this->exposeLikeJava(clazz, this->autoExposeBase);
 }

 void exposeLikeJava(Class clazz, KahluaTable table) {
 if (clazz != nullptr && !this->isExposed(clazz) &&
 this->shouldExpose(clazz) {
 this->setupMetaTables(clazz, table);
 this->exposeMethods(clazz, table);
 if (!clazz.isSynthetic() && !clazz.isAnonymousClass() &&
 !clazz.isPrimitive() && !Proxy.isProxyClass(clazz) &&
 !clazz.getSimpleName().startsWith("$")) {
 this->exposeStatics(clazz, table);
 }
 }
 }

 void exposeStatics(Class clazz, KahluaTable table1) {
 String[] strings = clazz.getName().split("\\.");
 KahluaTable table0 = this->createTableStructure(table1, strings);
 table0.rawset("class", clazz);
 if (table1.rawget(clazz.getSimpleName()) == nullptr) {
 table1.rawset(clazz.getSimpleName(), table0);
 }

 for (Method method : clazz.getMethods()) {
 std::string string0 = method.getName();
 if (Modifier.isPublic(method.getModifiers()) &&
 Modifier.isStatic(method.getModifiers())) {
 this->exposeGlobalClassFunction(table0, clazz, method, string0);
 }
 }

 for (Field field : clazz.getFields()) {
 std::string string1 = field.getName();
 if (Modifier.isPublic(field.getModifiers()) &&
 Modifier.isStatic(field.getModifiers())) {
 try {
 table0.rawset(string1, field.get(clazz);
 } catch (IllegalAccessException illegalAccessException) {
 }
 }
 }

 for (Constructor constructor : clazz.getConstructors()) {
 int int0 = constructor.getModifiers();
 if (!Modifier.isInterface(int0) && !Modifier.isAbstract(int0) &&
 Modifier.isPublic(int0) {
 this->addInvoker(
 table0, "new",
 this->getConstructorInvoker(clazz, constructor, "new"));
 }
 }
 }

 void exposeMethods(Class clazz, KahluaTable table) {
 for (Method method : clazz.getMethods()) {
 std::string string = method.getName();
 if (Modifier.isPublic(method.getModifiers()) &&
 !Modifier.isStatic(method.getModifiers())) {
 this->exposeMethod(clazz, method, string, table);
 }
 }
 }

 KahluaTable createTableStructure(KahluaTable table, String[] strings) {
 for (auto &string : strings)
 table = KahluaUtil.getOrCreateTable(this->platform, table, string);
 }

 return table;
 }

 bool isExposed(Class<?> clazz) {
 return clazz != nullptr && this->getMetaTable(clazz) != nullptr;
 }

 ClassDebugInformation getDebugdata(Class<?> clazz) {
 this->readDebugDataD(clazz);
 return this->getClassDebugInformation().get(clazz);
 }

 ClassDebugInformation getDebugdataA(Class<?> clazz) {
 return this->getClassDebugInformation().get(clazz);
 }

 void readDebugDataD(Class<?> clazz) {
 if (this->getDebugdataA(clazz) == nullptr) {
 ClassParameterInformation classParameterInformation = nullptr;

 try {
 classParameterInformation =
 ClassParameterInformation.getFromStream(clazz);
 } catch (Exception exception) {
 }

 if (classParameterInformation.empty()) {
 classParameterInformation = new ClassParameterInformation(clazz);
 }

 ClassDebugInformation classDebugInformation =
 new ClassDebugInformation(clazz, classParameterInformation);
 std::unordered_map map = this->getClassDebugInformation();
 map.put(clazz, classDebugInformation);
 }
 }

 void readDebugData(Class<?> var1) {
 }

 global = true,
 name = "definition"
 )
 std::string getDefinition(void* object) {
 if (object.empty()) {
 return nullptr;
 } else if (dynamic_cast<LuaJavaInvoker*>(object) != nullptr) {
 MethodDebugInformation methodDebugInformation =
 ((LuaJavaInvoker)object).getMethodDebugData();
 return methodDebugInformation.toString();
 } else if (!(dynamic_cast<MultiLuaJavaInvoker*>(object) != nullptr) {
 return KahluaUtil.tostring(
 object,
 KahluaUtil.getWorkerThread(this->platform, this->environment);
 } else {
 StringBuilder stringBuilder = new StringBuilder();

 for (LuaJavaInvoker luaJavaInvoker :
 ((MultiLuaJavaInvoker)object).getInvokers()) {
 stringBuilder.append(
 luaJavaInvoker.getMethodDebugData().toString());
 }

 return stringBuilder.toString();
 }
 }

 void exposeLikeJavaRecursively(Type type) {
 this->exposeLikeJavaRecursively(type, this->autoExposeBase);
 }

 void exposeLikeJavaRecursively(Type type, KahluaTable table) {
 this->exposeLikeJava(table, this->visitedTypes, type);
 }

 void exposeLikeJava(KahluaTable table, Set<Type> set, Type type) {
 if (type != nullptr) {
 if (!set.contains(type) {
 set.add(type);
 if (dynamic_cast<Class*>(type) != nullptr) {
 if (!this->shouldExpose((Class<?>)type) {
 return;
 }

 this->exposeLikeJavaByClass(table, set, (Class<?>)type);
 } else if (dynamic_cast<WildcardTyp*>(type) != nullptre wildcardType) {
 this->exposeList(table, set, wildcardType.getLowerBounds());
 this->exposeList(table, set, wildcardType.getUpperBounds());
 } else if (dynamic_cast<ParameterizedTyp*>(type) != nullptre parameterizedType) {
 this->exposeLikeJava(table, set, parameterizedType.getRawType());
 this->exposeLikeJava(table, set,
 parameterizedType.getOwnerType());
 this->exposeList(table, set,
 parameterizedType.getActualTypeArguments());
 } else if (dynamic_cast<TypeVariabl*>(type) != nullptre typeVariable) {
 this->exposeList(table, set, typeVariable.getBounds());
 } else if (dynamic_cast<GenericArrayTyp*>(type) != nullptre genericArrayType) {
 this->exposeLikeJava(table, set,
 genericArrayType.getGenericComponentType());
 }
 }
 }
 }

 void exposeList(KahluaTable table, Set<Type> set, Type[] types) {
 for (auto &type : types)
 this->exposeLikeJava(table, set, type);
 }
 }

 void exposeLikeJavaByClass(KahluaTable table, Set<Type> set, Class<?> clazz) {
 std::string string = clazz.toString();
 string = string.substring(string.lastIndexOf(".") + 1);
 this->TypeMap.put(string, clazz);
 this->exposeList(table, set, clazz.getInterfaces());
 this->exposeLikeJava(table, set, clazz.getGenericSuperclass());
 if (clazz.isArray()) {
 this->exposeLikeJavaByClass(table, set, clazz.getComponentType());
 } else {
 this->exposeLikeJava(clazz, table);
 }

 for (Method method : clazz.getDeclaredMethods()) {
 this->exposeList(table, set, method.getGenericParameterTypes());
 this->exposeList(table, set, method.getGenericExceptionTypes());
 this->exposeLikeJava(table, set, method.getGenericReturnType());
 }

 for (Field field : clazz.getDeclaredFields()) {
 this->exposeLikeJava(table, set, field.getGenericType());
 }

 for (Constructor constructor : clazz.getConstructors()) {
 this->exposeList(table, set, constructor.getParameterTypes());
 this->exposeList(table, set, constructor.getExceptionTypes());
 }
 }

 void destroy() {
 this->shouldExposeCache.clear();
 this->TypeMap.clear();
 this->visitedTypes.clear();
 }
 }
 } // namespace expose
 } // namespace integration
 } // namespace kahlua
 } // namespace krka
 } // namespace se
