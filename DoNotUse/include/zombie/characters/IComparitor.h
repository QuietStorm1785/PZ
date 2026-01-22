#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {

class IComparitor {
public:
    virtual ~IComparitor() = default;
    bool test(IsoGameCharacter var1, IsoGameCharacter var2);
}
} // namespace characters
} // namespace zombie
