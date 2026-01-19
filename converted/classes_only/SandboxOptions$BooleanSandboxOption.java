package zombie;

import se.krka.kahlua.vm.KahluaTable;
import zombie.Lua.LuaManager;
import zombie.SandboxOptions.SandboxOption;
import zombie.config.BooleanConfigOption;
import zombie.config.ConfigOption;
import zombie.core.Translator;

public class SandboxOptions$BooleanSandboxOption extends BooleanConfigOption implements SandboxOption {
   protected String translation;
   protected String tableName;
   protected String shortName;
   protected boolean bCustom;
   protected String pageName;

   public SandboxOptions$BooleanSandboxOption(SandboxOptions var1, String var2, boolean var3) {
      super(var2, var3);
      String[] var4 = SandboxOptions.parseName(var2);
      this.tableName = var4[0];
      this.shortName = var4[1];
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
      return Translator.getTextOrNull("Sandbox_" + (this.translation == null ? this.getShortName() : this.translation) + "_tooltip");
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
}
