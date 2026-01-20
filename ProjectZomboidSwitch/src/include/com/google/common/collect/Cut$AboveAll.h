#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace collect {

class Cut {
public:
   private static const Cut$AboveAll INSTANCE = new Cut$AboveAll();
    static const long serialVersionUID = 0L;

   private Cut$AboveAll() {
      super(nullptr);
   }

   Comparable<?> endpoint() {
      throw IllegalStateException("range unbounded on this side");
   }

    bool isLessThan(Comparable<?> value) {
    return false;
   }

    BoundType typeAsLowerBound() {
      throw AssertionError("this statement should be unreachable");
   }

    BoundType typeAsUpperBound() {
      throw std::make_unique<IllegalStateException>();
   }

   Cut<Comparable<?>> withLowerBoundType(BoundType boundType, DiscreteDomain<Comparable<?>> domain) {
      throw AssertionError("this statement should be unreachable");
   }

   Cut<Comparable<?>> withUpperBoundType(BoundType boundType, DiscreteDomain<Comparable<?>> domain) {
      throw std::make_unique<IllegalStateException>();
   }

    void describeAsLowerBound(std::stringstream sb) {
      throw std::make_unique<AssertionError>();
   }

    void describeAsUpperBound(std::stringstream sb) {
      sb.append("+∞)");
   }

   Comparable<?> leastValueAbove(DiscreteDomain<Comparable<?>> domain) {
      throw std::make_unique<AssertionError>();
   }

   Comparable<?> greatestValueBelow(DiscreteDomain<Comparable<?>> domain) {
      return domain.maxValue();
   }

    int compareTo(Cut<Comparable<?>> o) {
    return o = = this ? 0 : 1;
   }

    std::string toString() {
      return "+∞";
   }

    void* readResolve() {
    return INSTANCE;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
