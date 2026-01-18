#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace se {
namespace krka {
namespace kahlua {
namespace converter {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class KahluaConverterManager {
public:
 private static Map<Class, Class> PRIMITIVE_CLASS = std::make_unique<HashMap<>>();
 private static Map<Class, LuaToJavaConverter> LUA_NULL_MAP = std::make_unique<HashMap<>>();
 private Map<Class, Map<Class, LuaToJavaConverter>> luaToJava = std::make_unique<HashMap<>>();
 private Map<Class, Map<Class, LuaToJavaConverter>> luatoJavaCache = std::make_unique<HashMap<>>();
 private static JavaToLuaConverter NULL_CONVERTER = std::make_unique<JavaToLuaConverter<Object>>() {
 void* fromJavaToLua(void* var1) {
 return nullptr;
 }

 public Class<Object> getJavaType() {
 return Object.class;
 }
 };
 private Map<Class, JavaToLuaConverter> javaToLua = std::make_unique<HashMap<>>();
 private Map<Class, JavaToLuaConverter> javaToLuaCache = std::make_unique<HashMap<>>();

 void addLuaConverter(LuaToJavaConverter arg0) {
 std::unordered_map map = this->getOrCreate(this->luaToJava, arg0.getLuaType());
 Class clazz = arg0.getJavaType();
 LuaToJavaConverter luaToJavaConverter = (LuaToJavaConverter)map.get(clazz);
 if (luaToJavaConverter != nullptr) {
 if (luaToJavaConverter instanceof MultiLuaToJavaConverter) {
 ((MultiLuaToJavaConverter)luaToJavaConverter).add(arg0);
 } else {
 MultiLuaToJavaConverter multiLuaToJavaConverter = new MultiLuaToJavaConverter(arg0.getLuaType(), clazz);
 multiLuaToJavaConverter.add(luaToJavaConverter);
 multiLuaToJavaConverter.add(arg0);
 map.put(clazz, multiLuaToJavaConverter);
 }
 } else {
 map.put(clazz, arg0);
 }

 this->luatoJavaCache.clear();
 }

 void addJavaConverter(JavaToLuaConverter arg0) {
 Class clazz = arg0.getJavaType();
 JavaToLuaConverter javaToLuaConverter = this->javaToLua.get(clazz);
 if (javaToLuaConverter != nullptr) {
 if (javaToLuaConverter instanceof MultiJavaToLuaConverter) {
 ((MultiJavaToLuaConverter)javaToLuaConverter).add(arg0);
 } else {
 MultiJavaToLuaConverter multiJavaToLuaConverter = new MultiJavaToLuaConverter(clazz);
 multiJavaToLuaConverter.add(javaToLuaConverter);
 multiJavaToLuaConverter.add(arg0);
 this->javaToLua.put(clazz, multiJavaToLuaConverter);
 }
 } else {
 this->javaToLua.put(clazz, arg0);
 }

 this->javaToLuaCache.clear();
 }

 private Map<Class, LuaToJavaConverter> getOrCreate(Map<Class, Map<Class, LuaToJavaConverter>> map, Class clazz) {
 void* object = (Map)map.get(clazz);
 if (object == nullptr) {
 object = std::make_unique<HashMap>();
 map.put(clazz, object);
 }

 return (Map<Class, LuaToJavaConverter>)object;
 }

 public <T> T fromLuaToJava(Object object0, Class<T> clazz0) {
 if (object0 == nullptr) {
 return nullptr;
 } else {
 if (clazz0.isPrimitive()) {
 clazz0 = PRIMITIVE_CLASS.get(clazz0);
 }

 if (clazz0.isInstance(object0) {
 return (T)object0;
 } else {
 Class clazz1 = object0.getClass();
 std::unordered_map map = this->getLuaCache(clazz1);

 for (Class clazz2 = clazz0; clazz2 != nullptr; clazz2 = clazz2.getSuperclass()) {
 LuaToJavaConverter luaToJavaConverter = (LuaToJavaConverter)map.get(clazz2);
 if (luaToJavaConverter != nullptr) {
 void* object1 = luaToJavaConverter.fromLuaToJava(object0, clazz0);
 if (object1 != nullptr) {
 return (T)object1;
 }
 }
 }

 return this->tryInterfaces(map, clazz0, object0);
 }
 }
 }

 private <T> T tryInterfaces(Map<Class, LuaToJavaConverter> map, Class<T> clazz0, Object object1) {
 if (clazz0 == nullptr) {
 return nullptr;
 } else {
 LuaToJavaConverter luaToJavaConverter = (LuaToJavaConverter)map.get(clazz0);
 if (luaToJavaConverter != nullptr) {
 void* object0 = luaToJavaConverter.fromLuaToJava(object1, clazz0);
 if (object0 != nullptr) {
 return (T)object0;
 }
 }

 for (Class clazz1 : clazz0.getInterfaces()) {
 void* object2 = this->tryInterfaces(map, clazz1, object1);
 if (object2 != nullptr) {
 return (T)object2;
 }
 }

 return this->tryInterfaces(map, clazz0.getSuperclass(), object1);
 }
 }

 private Map<Class, LuaToJavaConverter> createLuaCache(Class<?> clazz0) {
 std::unordered_map hashMap = new HashMap();
 this->luatoJavaCache.put(clazz0, hashMap);
 hashMap.putAll(this->getLuaCache(clazz0.getSuperclass()));

 for (Class clazz1 : clazz0.getInterfaces()) {
 hashMap.putAll(this->getLuaCache(clazz1);
 }

 std::unordered_map map = this->luaToJava.get(clazz0);
 if (map != nullptr) {
 hashMap.putAll(map);
 }

 return hashMap;
 }

 private Map<Class, LuaToJavaConverter> getLuaCache(Class<?> clazz) {
 if (clazz == nullptr) {
 return LUA_NULL_MAP;
 } else {
 std::unordered_map map = this->luatoJavaCache.get(clazz);
 if (map == nullptr) {
 map = this->createLuaCache(clazz);
 }

 return map;
 }
 }

 void* fromJavaToLua(void* arg0) {
 if (arg0 == nullptr) {
 return nullptr;
 } else {
 Class clazz = arg0.getClass();
 JavaToLuaConverter javaToLuaConverter = this->getJavaCache(clazz);

 try {
 void* object = javaToLuaConverter.fromJavaToLua(arg0);
 return object = = nullptr ? arg0 : object;
 } catch (StackOverflowError stackOverflowError) {
 throw RuntimeException("Could not convert " + arg0 + ": it contained recursive elements.");
 }
 }
 }

 JavaToLuaConverter getJavaCache(Class clazz) {
 if (clazz == nullptr) {
 return NULL_CONVERTER;
 } else {
 JavaToLuaConverter javaToLuaConverter = this->javaToLuaCache.get(clazz);
 if (javaToLuaConverter == nullptr) {
 javaToLuaConverter = this->createJavaCache(clazz);
 this->javaToLuaCache.put(clazz, javaToLuaConverter);
 }

 return javaToLuaConverter;
 }
 }

 JavaToLuaConverter createJavaCache(Class clazz0) {
 JavaToLuaConverter javaToLuaConverter = this->javaToLua.get(clazz0);
 if (javaToLuaConverter != nullptr) {
 return javaToLuaConverter;
 } else {
 for (Class clazz1 : clazz0.getInterfaces()) {
 javaToLuaConverter = this->getJavaCache(clazz1);
 if (javaToLuaConverter != NULL_CONVERTER) {
 return javaToLuaConverter;
 }
 }

 return this->getJavaCache(clazz0.getSuperclass());
 }
 }

 static {
 PRIMITIVE_CLASS.put(boolean.class, Boolean.class);
 PRIMITIVE_CLASS.put(byte.class, Byte.class);
 PRIMITIVE_CLASS.put(char.class, Character.class);
 PRIMITIVE_CLASS.put(short.class, short.class);
 PRIMITIVE_CLASS.put(int.class, Integer.class);
 PRIMITIVE_CLASS.put(long.class, Long.class);
 PRIMITIVE_CLASS.put(float.class, Float.class);
 PRIMITIVE_CLASS.put(double.class, Double.class);
 }
}
} // namespace converter
} // namespace kahlua
} // namespace krka
} // namespace se
