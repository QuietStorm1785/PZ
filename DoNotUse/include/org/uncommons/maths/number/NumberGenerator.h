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

class NumberGenerator {
public:
    virtual ~NumberGenerator() = default;
    T nextValue();
}
} // namespace number
} // namespace maths
} // namespace uncommons
} // namespace org
