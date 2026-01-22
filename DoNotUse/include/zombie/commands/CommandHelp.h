#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace commands {


public @interface CommandHelp {
    std::string helpText();

    bool shouldTranslated();
}
} // namespace commands
} // namespace zombie
