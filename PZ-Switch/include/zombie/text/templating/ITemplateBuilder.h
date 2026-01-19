#pragma once
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace text {
namespace templating {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * TurboTuTone.
 */
class ITemplateBuilder {
public:
 virtual ~ITemplateBuilder() = default;
 std::string Build(std::string_view input);

 std::string Build(std::string_view input, IReplaceProvider replaceProvider);

 std::string Build(std::string_view input, KahluaTableImpl table);

 void RegisterKey(std::string_view key, KahluaTableImpl table);

 void RegisterKey(std::string_view key, IReplace replace);

 void Reset();
}
} // namespace templating
} // namespace text
} // namespace zombie
