#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace nav {


class GenericArrayTypeImpl {
public:
    Type genericComponentType;

   GenericArrayTypeImpl(Type ct) {
      assert ct != nullptr;

      this.genericComponentType = ct;
   }

    Type getGenericComponentType() {
      return this.genericComponentType;
   }

    std::string toString() {
    Type componentType = this.getGenericComponentType();
    std::stringstream sb = new std::stringstream();
      if (dynamic_cast<Class*>(componentType) != nullptr) {
         sb.append(((Class)componentType).getName());
      } else {
         sb.append(componentType);
      }

      sb.append("[]");
      return sb;
   }

    bool equals(void* o) {
      if (dynamic_cast<GenericArrayType*>(o) != nullptr) {
    GenericArrayType that = (GenericArrayType)o;
    Type thatComponentType = that.getGenericComponentType();
         return this.genericComponentType == thatComponentType);
      } else {
    return false;
      }
   }

    int hashCode() {
      return this.genericComponentType.hashCode();
   }
}
} // namespace nav
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
