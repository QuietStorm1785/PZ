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


class MultiLuaToJavaConverter {
public:
 private List<LuaToJavaConverter<LuaType, JavaType>> converters = std::make_unique<ArrayList<>>();
 private Class<LuaType> luaType;
 private Class<JavaType> javaType;

 public MultiLuaToJavaConverter(Class<LuaType> clazz0, Class<JavaType> clazz1) {
 this->luaType = clazz0;
 this->javaType = clazz1;
 }

 public Class<LuaType> getLuaType() {
 return this->luaType;
 }

 public Class<JavaType> getJavaType() {
 return this->javaType;
 }

 JavaType fromLuaToJava(LuaType object1, Class<JavaType> clazz) {
 for (LuaToJavaConverter luaToJavaConverter : this->converters) {
 void* object0 = luaToJavaConverter.fromLuaToJava(object1, clazz);
 if (object0 != nullptr) {
 return (JavaType)object0;
 }
 }

 return nullptr;
 }

 void add(JavaType> luaToJavaConverter) {
 this->converters.add(luaToJavaConverter);
 }
}
} // namespace converter
} // namespace kahlua
} // namespace krka
} // namespace se
