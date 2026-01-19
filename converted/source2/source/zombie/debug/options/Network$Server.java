package zombie.debug.options;

import zombie.debug.BooleanDebugOption;

public final class Network$Server extends OptionGroup {
   public final BooleanDebugOption SyncIsoObject;

   public Network$Server(Network var1, IDebugOptionGroup var2) {
      super(var2, "Server");
      this.this$0 = var1;
      this.SyncIsoObject = newDebugOnlyOption(this.Group, "SyncIsoObject", true);
   }
}
