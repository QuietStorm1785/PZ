#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace base {


class Predicates {
public:
   private const List<? : public Predicate<? super T>> components;
    static const long serialVersionUID = 0L;

   private Predicates$OrPredicate(List<? : public Predicate<? super T>> components) {
      this.components = components;
   }

    bool apply(@Nullable T) {
      for (int i = 0; i < this.components.size(); i++) {
         if (this.components.get(i).apply(t)) {
    return true;
         }
      }

    return false;
   }

    int hashCode() {
      return this.components.hashCode() + 87855567;
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<Predicates*>(obj) != nullptr$OrPredicate) {
         Predicates$OrPredicate<?> that = (Predicates$OrPredicate<?>)obj;
         return this.components == that.components);
      } else {
    return false;
      }
   }

    std::string toString() {
      return "Predicates.or(" + Predicates.access$800().join(this.components) + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
