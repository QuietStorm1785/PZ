#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/Cut/AboveAll.h"
#include "com/google/common/collect/Cut/AboveValue.h"
#include "com/google/common/collect/Cut/BelowAll.h"
#include "com/google/common/collect/Cut/BelowValue.h"
#include "com/google/common/primitives/Booleans.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class Cut {
public:
    const C endpoint;
    static const long serialVersionUID = 0L;

   Cut(@Nullable C endpoint) {
      this.endpoint = endpoint;
   }

   abstract boolean isLessThan(C var1);

   abstract BoundType typeAsLowerBound();

   abstract BoundType typeAsUpperBound();

   abstract Cut<C> withLowerBoundType(BoundType var1, DiscreteDomain<C> var2);

   abstract Cut<C> withUpperBoundType(BoundType var1, DiscreteDomain<C> var2);

   abstract void describeAsLowerBound(std::stringstream var1);

   abstract void describeAsUpperBound(std::stringstream var1);

   abstract C leastValueAbove(DiscreteDomain<C> var1);

   abstract C greatestValueBelow(DiscreteDomain<C> var1);

   Cut<C> canonical(DiscreteDomain<C> domain) {
    return this;
   }

    int compareTo(Cut<C> that) {
      if (that == belowAll()) {
    return 1;
      } else if (that == aboveAll()) {
         return -1;
      } else {
    int result = Range.compareOrThrow(this.endpoint, that.endpoint);
         return result != 0 ? result : Booleans.compare(dynamic_cast<AboveValue*>(this) != nullptr, dynamic_cast<AboveValue*>(that) != nullptr);
      }
   }

    C endpoint() {
      return this.endpoint;
   }

    bool equals(void* obj) {
      if (dynamic_cast<Cut*>(obj) != nullptr) {
         Cut<C> that = (Cut<C>)obj;

         try {
    int compareResult = this.compareTo(that);
    return compareResult = = 0;
         } catch (ClassCastException var4) {
         }
      }

    return false;
   }

   static <C : public Comparable> Cut<C> belowAll() {
      return BelowAll.access$000();
   }

   static <C : public Comparable> Cut<C> aboveAll() {
      return AboveAll.access$100();
   }

   static <C : public Comparable> Cut<C> belowValue(C endpoint) {
      return std::make_shared<BelowValue>(endpoint);
   }

   static <C : public Comparable> Cut<C> aboveValue(C endpoint) {
      return std::make_shared<AboveValue>(endpoint);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
