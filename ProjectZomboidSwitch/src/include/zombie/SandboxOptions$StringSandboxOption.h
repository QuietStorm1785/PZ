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
#include "zombie/config/StringConfigOption.h"
#include "zombie/core/Translator.h"

namespace zombie {


class SandboxOptions {
public:
    std::string translation;
    std::string tableName;
    std::string shortName;
    bool bCustom;
    std::string pageName;

   public SandboxOptions$StringSandboxOption(SandboxOptions var1, std::string var2, std::string var3, int var4) {
      super(var2, var3, var4);
      std::string[] var5 = SandboxOptions.parseName(var2);
      this.tableName = var5[0];
      this.shortName = var5[1];
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
      return Translator.getTextOrNull("Sandbox_" + (this.translation == nullptr ? this.getShortName() : this.translation) + "_tooltip");
   }


   void fromTable(lua_State* L, int index) {
      if (!this.tableName.empty()) {
         lua_getfield(L, index, this.tableName.c_str());
         if (lua_istable(L, -1)) {
            index = lua_gettop(L);
         } else {
            lua_pop(L, 1);
            return;
         }
      }
      lua_getfield(L, index, this.getShortName().c_str());
      if (!lua_isnil(L, -1)) {
         std::string value = lua_tostring(L, -1);
         this.setValueFromObject(value);
      }
      lua_pop(L, 1);
      if (!this.tableName.empty()) {
         lua_pop(L, 1);
      }
   }


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
      lua_pushstring(L, this.getValueAsObject().c_str());
      lua_setfield(L, tableIndex, this.getShortName().c_str());
      if (!this.tableName.empty()) {
         lua_pop(L, 1);
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
