#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace base {


class Predicates {
public:
   private const Class<?> clazz;
    static const long serialVersionUID = 0L;

   private Predicates$InstanceOfPredicate(Class<?> clazz) {
      this.clazz = (Class<?>)Preconditions.checkNotNull(clazz);
   }

    bool apply(@Nullable Object) {
      return this.clazz.isInstance(o);
   }

    int hashCode() {
      return this.clazz.hashCode();
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<Predicates*>(obj) != nullptr$InstanceOfPredicate) {
         Predicates$InstanceOfPredicate that = (Predicates$InstanceOfPredicate)obj;
         return this.clazz == that.clazz;
      } else {
    return false;
      }
   }

    std::string toString() {
      return "Predicates.instanceOf(" + this.clazz.getName() + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
