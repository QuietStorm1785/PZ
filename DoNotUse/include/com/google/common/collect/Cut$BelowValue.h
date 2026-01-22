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
#include "com/google/common/collect/Cut/AboveValue.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Cut {
public:
    static const long serialVersionUID = 0L;

   Cut$BelowValue(C endpoint) {
      super((Comparable)Preconditions.checkNotNull(endpoint));
   }

    bool isLessThan(C value) {
      return Range.compareOrThrow(this.endpoint, value) <= 0;
   }

    BoundType typeAsLowerBound() {
      return BoundType.CLOSED;
   }

    BoundType typeAsUpperBound() {
      return BoundType.OPEN;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   Cut<C> withLowerBoundType(BoundType boundType, DiscreteDomain<C> domain) {
      switch (1.$SwitchMap$com$google$common$collect$BoundType[boundType.ordinal()]) {
         case 1:
    return this;
         case 2:
    C previous = (C)domain.previous(this.endpoint);
            return (Cut<C>)(previous == nullptr ? Cut.belowAll() : std::make_shared<AboveValue>(previous));
         default:
            throw std::make_unique<AssertionError>();
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   Cut<C> withUpperBoundType(BoundType boundType, DiscreteDomain<C> domain) {
      switch (1.$SwitchMap$com$google$common$collect$BoundType[boundType.ordinal()]) {
         case 1:
    C previous = (C)domain.previous(this.endpoint);
            return (Cut<C>)(previous == nullptr ? Cut.aboveAll() : std::make_shared<AboveValue>(previous));
         case 2:
    return this;
         default:
            throw std::make_unique<AssertionError>();
      }
   }

    void describeAsLowerBound(std::stringstream sb) {
      sb.append('[').append(this.endpoint);
   }

    void describeAsUpperBound(std::stringstream sb) {
      sb.append(this.endpoint).append(')');
   }

    C leastValueAbove(DiscreteDomain<C> domain) {
      return (C)this.endpoint;
   }

    C greatestValueBelow(DiscreteDomain<C> domain) {
      return (C)domain.previous(this.endpoint);
   }

    int hashCode() {
      return this.endpoint.hashCode();
   }

    std::string toString() {
      return "\\" + this.endpoint + "/";
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
