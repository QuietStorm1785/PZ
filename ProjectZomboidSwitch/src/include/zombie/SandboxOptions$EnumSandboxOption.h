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
#include "zombie/config/EnumConfigOption.h"
#include "zombie/core/Translator.h"

namespace zombie {


class SandboxOptions {
public:
    std::string translation;
    std::string tableName;
    std::string shortName;
    bool bCustom;
    std::string pageName;
    std::string valueTranslation;

   public SandboxOptions$EnumSandboxOption(SandboxOptions var1, std::string var2, int var3, int var4) {
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
    std::string var1 = Translator.getTextOrNull("Sandbox_" + (this.translation == nullptr ? this.getShortName() : this.translation) + "_tooltip");
    std::string var2 = this.getValueTranslationByIndexOrNull(this.defaultValue);
    std::string var3 = var2 == nullptr ? nullptr : Translator.getText("Sandbox_Default", var2);
      if (var1 == nullptr) {
    return var3;
      } else {
    return var3 = = nullptr ? var1 : var1 + "\\n" + var3;
      }
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
         int value = (int)lua_tointeger(L, -1);
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
      lua_pushinteger(L, this.getValueAsObject());
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

   public SandboxOptions$EnumSandboxOption setValueTranslation(std::string var1) {
      this.valueTranslation = var1;
    return this;
   }

    std::string getValueTranslation() {
      return this.valueTranslation != nullptr ? this.valueTranslation : (this.translation == nullptr ? this.getShortName() : this.translation);
   }

    std::string getValueTranslationByIndex(int var1) {
      if (var1 >= 1 && var1 <= this.getNumValues()) {
         return Translator.getText("Sandbox_" + this.getValueTranslation() + "_option" + var1);
      } else {
         throw std::make_unique<ArrayIndexOutOfBoundsException>();
      }
   }

    std::string getValueTranslationByIndexOrNull(int var1) {
      if (var1 >= 1 && var1 <= this.getNumValues()) {
         return Translator.getTextOrNull("Sandbox_" + this.getValueTranslation() + "_option" + var1);
      } else {
         throw std::make_unique<ArrayIndexOutOfBoundsException>();
      }
   }
}
} // namespace zombie
