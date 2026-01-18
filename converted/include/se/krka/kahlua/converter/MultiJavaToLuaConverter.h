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

class MultiJavaToLuaConverter {
public:
private
  final List<JavaToLuaConverter> converters = std::make_unique<ArrayList<>>();
private
  final Class<JavaType> clazz;

public
  MultiJavaToLuaConverter(Class<JavaType> clazzx) { this.clazz = clazzx; }

public
  Class<JavaType> getJavaType() { return this.clazz; }

  void *fromJavaToLua(JavaType object1) {
    for (JavaToLuaConverter javaToLuaConverter : this.converters) {
      void *object0 = javaToLuaConverter.fromJavaToLua(object1);
      if (object0 != nullptr) {
        return object0;
      }
    }

    return null;
  }

  void add(JavaToLuaConverter javaToLuaConverter) {
    this.converters.add(javaToLuaConverter);
  }
}
} // namespace converter
} // namespace kahlua
} // namespace krka
} // namespace se
