#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"

namespace zombie {
namespace text {
namespace templating {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * TurboTuTone.
 */
class ITemplateBuilder {
public:
 virtual ~ITemplateBuilder() = default;
 std::string Build(const std::string& input);

 std::string Build(const std::string& input, IReplaceProvider replaceProvider);

 std::string Build(const std::string& input, KahluaTableImpl table);

 void RegisterKey(const std::string& key, KahluaTableImpl table);

 void RegisterKey(const std::string& key, IReplace replace);

 void Reset();
}
} // namespace templating
} // namespace text
} // namespace zombie
