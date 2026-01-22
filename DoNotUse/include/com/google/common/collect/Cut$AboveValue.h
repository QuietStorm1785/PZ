#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Cut/1.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Cut {
public:
    static const long serialVersionUID = 0L;

   Cut$AboveValue(C endpoint) {
      super((Comparable)Preconditions.checkNotNull(endpoint));
   }

    bool isLessThan(C value) {
      return Range.compareOrThrow(this.endpoint, value) < 0;
   }

    BoundType typeAsLowerBound() {
      return BoundType.OPEN;
   }

    BoundType typeAsUpperBound() {
      return BoundType.CLOSED;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   Cut<C> withLowerBoundType(BoundType boundType, DiscreteDomain<C> domain) {
      switch (1.$SwitchMap$com$google$common$collect$BoundType[boundType.ordinal()]) {
         case 1:
    C next = (C)domain.next(this.endpoint);
    return next = = nullptr ? Cut.belowAll() : belowValue(next);
         case 2:
    return this;
         default:
            throw std::make_unique<AssertionError>();
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   Cut<C> withUpperBoundType(BoundType boundType, DiscreteDomain<C> domain) {
      switch (1.$SwitchMap$com$google$common$collect$BoundType[boundType.ordinal()]) {
         case 1:
    return this;
         case 2:
    C next = (C)domain.next(this.endpoint);
    return next = = nullptr ? Cut.aboveAll() : belowValue(next);
         default:
            throw std::make_unique<AssertionError>();
      }
   }

    void describeAsLowerBound(std::stringstream sb) {
      sb.append('(').append(this.endpoint);
   }

    void describeAsUpperBound(std::stringstream sb) {
      sb.append(this.endpoint).append(']');
   }

    C leastValueAbove(DiscreteDomain<C> domain) {
      return (C)domain.next(this.endpoint);
   }

    C greatestValueBelow(DiscreteDomain<C> domain) {
      return (C)this.endpoint;
   }

   Cut<C> canonical(DiscreteDomain<C> domain) {
    C next = this.leastValueAbove(domain);
      return next != nullptr ? belowValue(next) : Cut.aboveAll();
   }

    int hashCode() {
      return ~this.endpoint.hashCode();
   }

    std::string toString() {
      return "/" + this.endpoint + "\\";
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
