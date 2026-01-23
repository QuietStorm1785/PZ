#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "zombie/config/ConfigOption.h"

namespace zombie {


class SandboxOptions {
public:
    virtual ~SandboxOptions() = default;
    ConfigOption asConfigOption();

    std::string getShortName();

    std::string getTableName();

   SandboxOptions$SandboxOption setTranslation(std::string var1);

    std::string getTranslatedName();

    std::string getTooltip();


    virtual void fromTable(lua_State* L, int index) = 0;
    virtual void toTable(lua_State* L, int index) = 0;

    void setCustom();

    bool isCustom();

   SandboxOptions$SandboxOption setPageName(std::string var1);

    std::string getPageName();
}
} // namespace zombie
