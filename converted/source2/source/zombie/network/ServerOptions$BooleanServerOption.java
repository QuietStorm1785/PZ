package zombie.network;

import zombie.config.BooleanConfigOption;
import zombie.config.ConfigOption;
import zombie.core.Translator;
import zombie.network.ServerOptions.ServerOption;

public class ServerOptions$BooleanServerOption extends BooleanConfigOption implements ServerOption {
   public ServerOptions$BooleanServerOption(ServerOptions var1, String var2, boolean var3) {
      super(var2, var3);
      var1.addOption(this);
   }

   public ConfigOption asConfigOption() {
      return this;
   }

   public String getTooltip() {
      return Translator.getTextOrNull("UI_ServerOption_" + this.name + "_tooltip");
   }
}
