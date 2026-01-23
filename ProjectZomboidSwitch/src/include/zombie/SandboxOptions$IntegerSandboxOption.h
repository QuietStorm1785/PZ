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
#include "zombie/SandboxOptions/SandboxOption.h"
#include "zombie/config/ConfigOption.h"
#include "zombie/config/IntegerConfigOption.h"
#include "zombie/core/Translator.h"

namespace zombie {


class SandboxOptions {
public:
    std::string translation;
    std::string tableName;
    std::string shortName;
    bool bCustom;
    std::string pageName;

   public SandboxOptions$IntegerSandboxOption(SandboxOptions var1, std::string var2, int var3, int var4, int var5) {
      super(var2, var3, var4, var5);
      std::string[] var6 = SandboxOptions.parseName(var2);
      this.tableName = var6[0];
      this.shortName = var6[1];
      var1.addOption(this);
   }

    ConfigOption asConfigOption() {
    return this;
   }

    std::string getShortName() {
      return this.shortName;
   }

    std::string getTableName() {
      return this.tableName;
   }

    SandboxOption setTranslation(const std::string& var1) {
      this.translation = var1;
    return this;
   }

    std::string getTranslatedName() {
      return Translator.getText("Sandbox_" + (this.translation == nullptr ? this.getShortName() : this.translation));
   }

    std::string getTooltip() {
    std::string var1;
      if ("ZombieConfig" == this.tableName)) {
         var1 = Translator.getTextOrNull("Sandbox_" + (this.translation == nullptr ? this.getShortName() : this.translation) + "_help");
      } else {
         var1 = Translator.getTextOrNull("Sandbox_" + (this.translation == nullptr ? this.getShortName() : this.translation) + "_tooltip");
      }

    std::string var2 = Translator.getText("Sandbox_MinMaxDefault", this.min, this.max, this.defaultValue);
      if (var1 == nullptr) {
    return var2;
      } else {
    return var2 = = nullptr ? var1 : var1 + "\\n" + var2;
      }
   }


    // Refactored: Load value from a Lua table on the stack at the given index
    void fromTable(lua_State* L, int index) {
      // Push tableName if present, else use current table
      if (!this.tableName.empty()) {
        lua_getfield(L, index, this.tableName.c_str()); // push tableName field
        if (lua_istable(L, -1)) {
          index = lua_gettop(L);
        } else {
          lua_pop(L, 1); // not a table, pop
          return;
        }
      }
      lua_getfield(L, index, this.getShortName().c_str());
      if (!lua_isnil(L, -1)) {
        // Assume integer for this option
        int value = (int)lua_tointeger(L, -1);
        this.setValueFromObject(value);
      }
      lua_pop(L, 1); // pop value
      if (!this.tableName.empty()) {
        lua_pop(L, 1); // pop tableName table
      }
    }


    // Refactored: Write value to a Lua table on the stack at the given index
    void toTable(lua_State* L, int index) {
      int tableIndex = index;
      if (!this.tableName.empty()) {
        lua_getfield(L, index, this.tableName.c_str());
        if (!lua_istable(L, -1)) {
          lua_pop(L, 1);
          lua_newtable(L);
          lua_pushvalue(L, -1);
          lua_setfield(L, index, this.tableName.c_str());
        }
        tableIndex = lua_gettop(L);
      }
      lua_pushinteger(L, this.getValueAsObject());
      lua_setfield(L, tableIndex, this.getShortName().c_str());
      if (!this.tableName.empty()) {
        lua_pop(L, 1); // pop tableName table
      }
    }

    void setCustom() {
      this.bCustom = true;
   }

    bool isCustom() {
      return this.bCustom;
   }

    SandboxOption setPageName(const std::string& var1) {
      this.pageName = var1;
    return this;
   }

    std::string getPageName() {
      return this.pageName;
   }
}
} // namespace zombie
