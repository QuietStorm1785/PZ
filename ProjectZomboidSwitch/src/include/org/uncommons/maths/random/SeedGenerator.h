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

class SeedGenerator {
public:
    virtual ~SeedGenerator() = default;
   byte[] generateSeed(int var1) throws SeedException;
}
} // namespace random
} // namespace maths
} // namespace uncommons
} // namespace org
