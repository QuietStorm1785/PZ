#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace org {
namespace uncommons {
namespace maths {
namespace number {

class ConstantGenerator {
public:
    const T constant;

    public ConstantGenerator(T constant) {
      this.constant = constant;
   }

    T nextValue() {
      return this.constant;
   }
}
} // namespace number
} // namespace maths
} // namespace uncommons
} // namespace org
