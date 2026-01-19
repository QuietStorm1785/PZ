package zombie;

import se.krka.kahlua.vm.KahluaTable;
import zombie.Lua.LuaManager;
import zombie.SandboxOptions.SandboxOption;
import zombie.config.ConfigOption;
import zombie.config.EnumConfigOption;
import zombie.core.Translator;

public class SandboxOptions$EnumSandboxOption extends EnumConfigOption implements SandboxOption {
   protected String translation;
   protected String tableName;
   protected String shortName;
   protected boolean bCustom;
   protected String pageName;
   protected String valueTranslation;

   public SandboxOptions$EnumSandboxOption(SandboxOptions var1, String var2, int var3, int var4) {
      super(var2, var3, var4);
      String[] var5 = SandboxOptions.parseName(var2);
      this.tableName = var5[0];
      this.shortName = var5[1];
      var1.addOption(this);
   }

   public ConfigOption asConfigOption() {
      return this;
   }

   public String getShortName() {
      return this.shortName;
   }

   public String getTableName() {
      return this.tableName;
   }

   public SandboxOption setTranslation(String var1) {
      this.translation = var1;
      return this;
   }

   public String getTranslatedName() {
      return Translator.getText("Sandbox_" + (this.translation == null ? this.getShortName() : this.translation));
   }

   public String getTooltip() {
      String var1 = Translator.getTextOrNull("Sandbox_" + (this.translation == null ? this.getShortName() : this.translation) + "_tooltip");
      String var2 = this.getValueTranslationByIndexOrNull(this.defaultValue);
      String var3 = var2 == null ? null : Translator.getText("Sandbox_Default", var2);
      if (var1 == null) {
         return var3;
      } else {
         return var3 == null ? var1 : var1 + "\\n" + var3;
      }
   }

   public void fromTable(KahluaTable var1xx) {
      if (this.tableName == null || var1xx.rawget(this.tableName) instanceof KahluaTable var1xx) {
         Object var3 = var1xx.rawget(this.getShortName());
         if (var3 != null) {
            this.setValueFromObject(var3);
         }
      }
   }

   public void toTable(KahluaTable var1xx) {
      if (this.tableName != null && !(var1xx.rawget(this.tableName) instanceof KahluaTable var1xx)) {
         KahluaTable var3 = LuaManager.platform.newTable();
         var1xx.rawset(this.tableName, var3);
         var1xx = var3;
      }

      var1xx.rawset(this.getShortName(), this.getValueAsObject());
   }

   public void setCustom() {
      this.bCustom = true;
   }

   public boolean isCustom() {
      return this.bCustom;
   }

   public SandboxOption setPageName(String var1) {
      this.pageName = var1;
      return this;
   }

   public String getPageName() {
      return this.pageName;
   }

   public SandboxOptions$EnumSandboxOption setValueTranslation(String var1) {
      this.valueTranslation = var1;
      return this;
   }

   public String getValueTranslation() {
      return this.valueTranslation != null ? this.valueTranslation : (this.translation == null ? this.getShortName() : this.translation);
   }

   public String getValueTranslationByIndex(int var1) {
      if (var1 >= 1 && var1 <= this.getNumValues()) {
         return Translator.getText("Sandbox_" + this.getValueTranslation() + "_option" + var1);
      } else {
         throw new ArrayIndexOutOfBoundsException();
      }
   }

   public String getValueTranslationByIndexOrNull(int var1) {
      if (var1 >= 1 && var1 <= this.getNumValues()) {
         return Translator.getTextOrNull("Sandbox_" + this.getValueTranslation() + "_option" + var1);
      } else {
         throw new ArrayIndexOutOfBoundsException();
      }
   }
}
