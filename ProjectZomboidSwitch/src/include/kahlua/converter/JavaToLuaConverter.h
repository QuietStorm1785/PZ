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

class JavaToLuaConverter {
public:
 virtual ~JavaToLuaConverter() = default;
 Class<JavaType> getJavaType();

 void *fromJavaToLua(JavaType var1);
}
} // namespace converter
} // namespace kahlua
} // namespace krka
} // namespace se
