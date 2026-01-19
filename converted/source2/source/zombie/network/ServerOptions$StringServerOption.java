package zombie.network;

import zombie.config.ConfigOption;
import zombie.config.StringConfigOption;
import zombie.core.Translator;
import zombie.network.ServerOptions.ServerOption;

public class ServerOptions$StringServerOption extends StringConfigOption implements ServerOption {
   public ServerOptions$StringServerOption(ServerOptions var1, String var2, String var3, int var4) {
      super(var2, var3, var4);
      var1.addOption(this);
   }

   public ConfigOption asConfigOption() {
      return this;
   }

   public String getTooltip() {
      return Translator.getTextOrNull("UI_ServerOption_" + this.name + "_tooltip");
   }
}
