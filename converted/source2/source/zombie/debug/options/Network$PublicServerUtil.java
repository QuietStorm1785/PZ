package zombie.debug.options;

import zombie.debug.BooleanDebugOption;

public final class Network$PublicServerUtil extends OptionGroup {
   public final BooleanDebugOption Enabled;

   public Network$PublicServerUtil(Network var1, IDebugOptionGroup var2) {
      super(var2, "PublicServerUtil");
      this.this$0 = var1;
      this.Enabled = newDebugOnlyOption(this.Group, "Enabled", true);
   }
}
