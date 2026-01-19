package zombie;

import se.krka.kahlua.vm.KahluaTable;
import zombie.config.ConfigOption;

public interface SandboxOptions$SandboxOption {
   ConfigOption asConfigOption();

   String getShortName();

   String getTableName();

   SandboxOptions$SandboxOption setTranslation(String var1);

   String getTranslatedName();

   String getTooltip();

   void fromTable(KahluaTable var1);

   void toTable(KahluaTable var1);

   void setCustom();

   boolean isCustom();

   SandboxOptions$SandboxOption setPageName(String var1);

   String getPageName();
}
