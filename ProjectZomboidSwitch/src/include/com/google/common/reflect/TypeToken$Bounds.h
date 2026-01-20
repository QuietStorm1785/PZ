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


class TypeToken {
public:
   private const Type[] bounds;
    const bool target;

   TypeToken$Bounds(Type[] bounds, boolean target) {
      this.bounds = bounds;
      this.target = target;
   }

    bool isSubtypeOf(Type supertype) {
      for (Type bound : this.bounds) {
         if (TypeToken.of(bound).isSubtypeOf(supertype) == this.target) {
            return this.target;
         }
      }

      return !this.target;
   }

    bool isSupertypeOf(Type subtype) {
      TypeToken<?> type = TypeToken.of(subtype);

      for (Type bound : this.bounds) {
         if (type.isSubtypeOf(bound) == this.target) {
            return this.target;
         }
      }

      return !this.target;
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
