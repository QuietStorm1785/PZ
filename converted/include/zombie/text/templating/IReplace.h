#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace text {
namespace templating {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

/**
 * TurboTuTone. Interface that provides (random) String for ITemplateBuilder.
 */
class IReplace {
public:
 virtual ~IReplace() = default;
 std::string getString();
}
} // namespace templating
} // namespace text
} // namespace zombie
