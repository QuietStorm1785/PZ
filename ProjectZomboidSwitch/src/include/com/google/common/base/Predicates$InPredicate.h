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
   private const Collection<?> target;
    static const long serialVersionUID = 0L;

   private Predicates$InPredicate(Collection<?> target) {
      this.target = (Collection<?>)Preconditions.checkNotNull(target);
   }

    bool apply(@Nullable T) {
      try {
         return this.target.contains(t);
      } catch (NullPointerException var3) {
    return false;
      } catch (ClassCastException var4) {
    return false;
      }
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<Predicates*>(obj) != nullptr$InPredicate) {
         Predicates$InPredicate<?> that = (Predicates$InPredicate<?>)obj;
         return this.target == that.target);
      } else {
    return false;
      }
   }

    int hashCode() {
      return this.target.hashCode();
   }

    std::string toString() {
      return "Predicates.in(" + this.target + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
