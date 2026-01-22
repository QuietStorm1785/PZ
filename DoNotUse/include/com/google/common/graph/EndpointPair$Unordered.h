#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class EndpointPair {
public:
   private EndpointPair$Unordered(N nodeU, N nodeV) {
      super(nodeU, nodeV, nullptr);
   }

    N source() {
      throw UnsupportedOperationException(
         "Cannot call source()/target() on a EndpointPair from an undirected graph. Consider calling adjacentNode(node) if you already have a node, or nodeU()/nodeV() if you don't."
      );
   }

    N target() {
      throw UnsupportedOperationException(
         "Cannot call source()/target() on a EndpointPair from an undirected graph. Consider calling adjacentNode(node) if you already have a node, or nodeU()/nodeV() if you don't."
      );
   }

    bool isOrdered() {
    return false;
   }

    bool equals(@Nullable Object) {
      if (obj == this) {
    return true;
      } else if (!(dynamic_cast<EndpointPair*>(obj) != nullptr)) {
    return false;
      } else {
         EndpointPair<?> other = (EndpointPair<?>)obj;
         if (this.isOrdered() != other.isOrdered()) {
    return false;
         } else {
            return this.nodeU() == other.nodeU())
               ? this.nodeV() == other.nodeV())
               : this.nodeU() == other.nodeV()) && this.nodeV() == other.nodeU());
         }
      }
   }

    int hashCode() {
      return this.nodeU().hashCode() + this.nodeV().hashCode();
   }

    std::string toString() {
      return std::string.format("[%s, %s]", this.nodeU(), this.nodeV());
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
