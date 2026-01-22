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
namespace base {

enum class Predicates {
   ALWAYS_TRUE,
   ALWAYS_FALSE,
   IS_NULL,
   NOT_NULL;

   private Predicates$ObjectPredicate() {
   }

   <T> Predicate<T> withNarrowedType() {
    return this;
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
