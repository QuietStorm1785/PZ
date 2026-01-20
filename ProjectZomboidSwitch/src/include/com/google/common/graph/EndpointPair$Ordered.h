#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Objects.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class EndpointPair {
public:
   private EndpointPair$Ordered(N source, N target) {
      super(source, target, nullptr);
   }

    N source() {
      return (N)this.nodeU();
   }

    N target() {
      return (N)this.nodeV();
   }

    bool isOrdered() {
    return true;
   }

    bool equals(@Nullable Object) {
      if (obj == this) {
    return true;
      } else if (!(dynamic_cast<EndpointPair*>(obj) != nullptr)) {
    return false;
      } else {
         EndpointPair<?> other = (EndpointPair<?>)obj;
         return this.isOrdered() != other.isOrdered() ? false : this.source() == other.source()) && this.target() == other.target());
      }
   }

    int hashCode() {
      return Objects.hashCode(new Object[]{this.source(), this.target()});
   }

    std::string toString() {
      return std::string.format("<%s -> %s>", this.source(), this.target());
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
