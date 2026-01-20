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
namespace random {

class RepeatableRNG {
public:
    virtual ~RepeatableRNG() = default;
   byte[] getSeed();
}
} // namespace random
} // namespace maths
} // namespace uncommons
} // namespace org
