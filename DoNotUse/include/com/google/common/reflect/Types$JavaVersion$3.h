#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace reflect {


enum class Types {
    Type newArrayType(Type componentType) {
      return JAVA7.newArrayType(componentType);
   }

    Type usedInGenericType(Type type) {
      return JAVA7.usedInGenericType(type);
   }

    std::string typeName(Type type) {
      try {
    Method getTypeName = Type.class.getMethod("getTypeName");
         return (std::string)getTypeName.invoke(type);
      } catch (NoSuchMethodException var3) {
         throw AssertionError("Type.getTypeName should be available in Java 8");
      } catch (InvocationTargetException var4) {
         throw RuntimeException(var4);
      } catch (IllegalAccessException var5) {
         throw RuntimeException(var5);
      }
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
