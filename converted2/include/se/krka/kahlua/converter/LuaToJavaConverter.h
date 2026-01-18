#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace converter {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class LuaToJavaConverter {
public:
  virtual ~LuaToJavaConverter() = default;
  Class<LuaType> getLuaType();

  Class<JavaType> getJavaType();

  JavaType fromLuaToJava(LuaType var1, Class<JavaType> var2);
}
} // namespace converter
} // namespace kahlua
} // namespace krka
} // namespace se
