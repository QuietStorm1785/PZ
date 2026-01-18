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
 * TurboTuTone. Interface that can provide IReplace for ITemplateBuilder. Any keys present in a IReplaceProvider take priority when replacing keys in a template. NOTE: When checking the key String, this should be equaling a lowercase version or equalsIgnoreCase
 */
class IReplaceProvider {
public:
 virtual ~IReplaceProvider() = default;
 bool hasReplacer(const std::string& key);

 IReplace getReplacer(const std::string& key);
}
} // namespace templating
} // namespace text
} // namespace zombie
