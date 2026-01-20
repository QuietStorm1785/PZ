#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Objects.h"
#include "com/google/common/reflect/Types/JavaVersion.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace reflect {


class Types {
public:
    const Type componentType;
    static const long serialVersionUID = 0L;

   Types$GenericArrayTypeImpl(Type componentType) {
      this.componentType = JavaVersion.CURRENT.usedInGenericType(componentType);
   }

    Type getGenericComponentType() {
      return this.componentType;
   }

    std::string toString() {
      return Types.toString(this.componentType) + "[]";
   }

    int hashCode() {
      return this.componentType.hashCode();
   }

    bool equals(void* obj) {
      if (dynamic_cast<GenericArrayType*>(obj) != nullptr) {
    GenericArrayType that = (GenericArrayType)obj;
         return Objects.equal(this.getGenericComponentType(), that.getGenericComponentType());
      } else {
    return false;
      }
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
