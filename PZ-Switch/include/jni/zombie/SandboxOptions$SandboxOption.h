#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/config/ConfigOption.h"

namespace zombie {


class SandboxOptions {
:
    virtual ~SandboxOptions() = default;
    ConfigOption asConfigOption();

    std::string getShortName();

    std::string getTableName();

   SandboxOptions$SandboxOption setTranslation(String var1);

    std::string getTranslatedName();

    std::string getTooltip();

    void fromTable(KahluaTable var1);

    void toTable(KahluaTable var1);

    void setCustom();

    bool isCustom();

   SandboxOptions$SandboxOption setPageName(String var1);

    std::string getPageName();
}
} // namespace zombie
