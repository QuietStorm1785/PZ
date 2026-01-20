#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Objects.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace eventbus {


class SubscriberRegistry {
public:
    const std::string name;
   private const List<Class<?>> parameterTypes;

   SubscriberRegistry$MethodIdentifier(Method method) {
      this.name = method.getName();
      this.parameterTypes = Arrays.asList(method.getParameterTypes());
   }

    int hashCode() {
      return Objects.hashCode(new Object[]{this.name, this.parameterTypes});
   }

    bool equals(@Nullable Object) {
      if (!(dynamic_cast<SubscriberRegistry*>(o) != nullptr$MethodIdentifier)) {
    return false;
      } else {
         SubscriberRegistry$MethodIdentifier ident = (SubscriberRegistry$MethodIdentifier)o;
         return this.name == ident.name) && this.parameterTypes == ident.parameterTypes);
      }
   }
}
} // namespace eventbus
} // namespace common
} // namespace google
} // namespace com
