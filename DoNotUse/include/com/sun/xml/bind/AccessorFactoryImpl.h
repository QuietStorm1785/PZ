#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor/FieldReflection.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor/GetterOnlyReflection.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor/GetterSetterReflection.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor/ReadOnlyFieldReflection.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor/SetterOnlyReflection.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {


class AccessorFactoryImpl {
public:
    static AccessorFactoryImpl instance = std::make_shared<AccessorFactoryImpl>();

    private AccessorFactoryImpl() {
   }

    static AccessorFactoryImpl getInstance() {
    return instance;
   }

    Accessor createFieldAccessor(Class bean, Field field, bool readOnly) {
      return (Accessor)(readOnly ? std::make_shared<ReadOnlyFieldReflection>(field) : std::make_shared<FieldReflection>(field));
   }

    Accessor createFieldAccessor(Class bean, Field field, bool readOnly, bool supressWarning) {
      return (Accessor)(readOnly ? std::make_shared<ReadOnlyFieldReflection>(field, supressWarning) : std::make_shared<FieldReflection>(field, supressWarning));
   }

    Accessor createPropertyAccessor(Class bean, Method getter, Method setter) {
      if (getter == nullptr) {
         return std::make_shared<SetterOnlyReflection>(setter);
      } else {
         return (Accessor)(setter == nullptr ? std::make_shared<GetterOnlyReflection>(getter) : std::make_shared<GetterSetterReflection>(getter, setter));
      }
   }
}
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
