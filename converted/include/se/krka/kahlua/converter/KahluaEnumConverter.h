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

class KahluaEnumConverter {
public:
 private KahluaEnumConverter() {
 }

 static void install(KahluaConverterManager kahluaConverterManager) {
 kahluaConverterManager.addJavaConverter(std::make_unique<JavaToLuaConverter<Enum>>() {
 void* fromJavaToLua(Enum _enum) {
 return _enum.name();
 }

 public Class<Enum> getJavaType() {
 return Enum.class;
 }
 });
 kahluaConverterManager.addLuaConverter(new LuaToJavaConverter<String, Enum>() {
 Enum fromLuaToJava(const std::string& string, Class<Enum> clazz) {
 return Enum.valueOf(clazz, string);
 }

 public Class<Enum> getJavaType() {
 return Enum.class;
 }

 public Class<String> getLuaType() {
 return String.class;
 }
 });
 }
}
} // namespace converter
} // namespace kahlua
} // namespace krka
} // namespace se
