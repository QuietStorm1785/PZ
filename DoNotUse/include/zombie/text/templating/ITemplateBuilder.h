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


class ITemplateBuilder {
public:
    virtual ~ITemplateBuilder() = default;
    std::string Build(const std::string& var1);

    std::string Build(const std::string& var1, IReplaceProvider var2);

    std::string Build(const std::string& var1, KahluaTableImpl var2);

    void RegisterKey(const std::string& var1, KahluaTableImpl var2);

    void RegisterKey(const std::string& var1, IReplace var2);

    void Reset();
}
} // namespace templating
} // namespace text
} // namespace zombie
