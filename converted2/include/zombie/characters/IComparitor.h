#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IComparitor {
public:
  virtual ~IComparitor() = default;
  bool test(IsoGameCharacter var1, IsoGameCharacter var2);
}
} // namespace characters
} // namespace zombie
