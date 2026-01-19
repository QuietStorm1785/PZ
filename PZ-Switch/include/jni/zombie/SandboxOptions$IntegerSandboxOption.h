#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/SandboxOptions/SandboxOption.h"
#include "zombie/config/ConfigOption.h"
#include "zombie/config/IntegerConfigOption.h"
#include "zombie/core/Translator.h"

namespace zombie {


class SandboxOptions {
:
    std::string translation;
    std::string tableName;
    std::string shortName;
    bool bCustom;
    std::string pageName;

    SandboxOptions$IntegerSandboxOption(SandboxOptions var1, String var2, int var3, int var4, int var5) {
      super(var2, var3, var4, var5);
      String[] var6 = SandboxOptions.parseName(var2);
      this.tableName = var6[0];
      this.shortName = var6[1];
      var1.addOption(this);
   }

    ConfigOption asConfigOption() {
    return this;
   }

    std::string getShortName() const {
      return this.shortName;
   }

    std::string getTableName() const {
      return this.tableName;
   }

    SandboxOption setTranslation(std::string_view var1) {
      this.translation = var1;
    return this;
   }

    std::string getTranslatedName() const {
      return Translator.getText("Sandbox_" + (this.translation == nullptr ? this.getShortName() : this.translation));
   }

    std::string getTooltip() const {
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

    void fromTable(KahluaTable var1xx) {
      if (this.tableName == nullptr || var1xx.rawget(this.tableName) instanceof KahluaTable var1xx) {
    void* var3 = var1xx.rawget(this.getShortName());
         if (var3 != nullptr) {
            this.setValueFromObject(var3);
         }
      }
   }

    void toTable(KahluaTable var1xx) {
      if (this.tableName != nullptr && !(var1xx.rawget(this.tableName) instanceof KahluaTable var1xx)) {
    KahluaTable var3 = LuaManager.platform.newTable();
         var1xx.rawset(this.tableName, var3);
         var1xx = var3;
      }

      var1xx.rawset(this.getShortName(), this.getValueAsObject());
   }

    void setCustom() {
      this.bCustom = true;
   }

    bool isCustom() {
      return this.bCustom;
   }

    SandboxOption setPageName(std::string_view var1) {
      this.pageName = var1;
    return this;
   }

    std::string getPageName() const {
      return this.pageName;
   }
}
} // namespace zombie
