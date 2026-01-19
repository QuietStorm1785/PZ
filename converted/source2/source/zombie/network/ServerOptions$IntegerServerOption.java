package zombie.network;

import zombie.config.ConfigOption;
import zombie.config.IntegerConfigOption;
import zombie.core.Translator;
import zombie.network.ServerOptions.ServerOption;

public class ServerOptions$IntegerServerOption extends IntegerConfigOption implements ServerOption {
   public ServerOptions$IntegerServerOption(ServerOptions var1, String var2, int var3, int var4, int var5) {
      super(var2, var3, var4, var5);
      var1.addOption(this);
   }

   public ConfigOption asConfigOption() {
      return this;
   }

   public String getTooltip() {
      String var1 = Translator.getTextOrNull("UI_ServerOption_" + this.name + "_tooltip");
      String var2 = Translator.getText("Sandbox_MinMaxDefault", this.min, this.max, this.defaultValue);
      if (var1 == null) {
         return var2;
      } else {
         return var2 == null ? var1 : var1 + "\\n" + var2;
      }
   }
}
