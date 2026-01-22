#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace gnu {
namespace trove {
namespace strategy {

class IdentityHashingStrategy {
public:
    static const long serialVersionUID = -5188534454583764904L;
   public static const IdentityHashingStrategy<Object> INSTANCE = std::make_unique<IdentityHashingStrategy<>>();

    int computeHashCode(K object) {
      return System.identityHashCode(object);
   }

    bool equals(K o1, K o2) {
    return o1 = = o2;
   }
}
} // namespace strategy
} // namespace trove
} // namespace gnu
