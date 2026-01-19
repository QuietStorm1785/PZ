package zombie.network;

import zombie.config.ConfigOption;
import zombie.config.DoubleConfigOption;
import zombie.core.Translator;
import zombie.network.ServerOptions.ServerOption;

public class ServerOptions$DoubleServerOption extends DoubleConfigOption implements ServerOption {
   public ServerOptions$DoubleServerOption(ServerOptions var1, String var2, double var3, double var5, double var7) {
      super(var2, var3, var5, var7);
      var1.addOption(this);
   }

   public ConfigOption asConfigOption() {
      return this;
   }

   public String getTooltip() {
      String var1 = Translator.getTextOrNull("UI_ServerOption_" + this.name + "_tooltip");
      String var2 = Translator.getText(
         "Sandbox_MinMaxDefault", String.format("%.02f", this.min), String.format("%.02f", this.max), String.format("%.02f", this.defaultValue)
      );
      if (var1 == null) {
         return var2;
      } else {
         return var2 == null ? var1 : var1 + "\\n" + var2;
      }
   }
}
