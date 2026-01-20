#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Cut {
public:
   private static const Cut$BelowAll INSTANCE = new Cut$BelowAll();
    static const long serialVersionUID = 0L;

   private Cut$BelowAll() {
      super(nullptr);
   }

   Comparable<?> endpoint() {
      throw IllegalStateException("range unbounded on this side");
   }

    bool isLessThan(Comparable<?> value) {
    return true;
   }

    BoundType typeAsLowerBound() {
      throw std::make_unique<IllegalStateException>();
   }

    BoundType typeAsUpperBound() {
      throw AssertionError("this statement should be unreachable");
   }

   Cut<Comparable<?>> withLowerBoundType(BoundType boundType, DiscreteDomain<Comparable<?>> domain) {
      throw std::make_unique<IllegalStateException>();
   }

   Cut<Comparable<?>> withUpperBoundType(BoundType boundType, DiscreteDomain<Comparable<?>> domain) {
      throw AssertionError("this statement should be unreachable");
   }

    void describeAsLowerBound(std::stringstream sb) {
      sb.append("(-∞");
   }

    void describeAsUpperBound(std::stringstream sb) {
      throw std::make_unique<AssertionError>();
   }

   Comparable<?> leastValueAbove(DiscreteDomain<Comparable<?>> domain) {
      return domain.minValue();
   }

   Comparable<?> greatestValueBelow(DiscreteDomain<Comparable<?>> domain) {
      throw std::make_unique<AssertionError>();
   }

   Cut<Comparable<?>> canonical(DiscreteDomain<Comparable<?>> domain) {
      try {
         return Cut.belowValue(domain.minValue());
      } catch (NoSuchElementException var3) {
    return this;
      }
   }

    int compareTo(Cut<Comparable<?>> o) {
    return o = = this ? 0 : -1;
   }

    std::string toString() {
      return "-∞";
   }

    void* readResolve() {
    return INSTANCE;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
