package zombie.debug.options;

import zombie.debug.BooleanDebugOption;

public final class Network$Client extends OptionGroup {
   public final BooleanDebugOption MainLoop;
   public final BooleanDebugOption UpdateZombiesFromPacket;
   public final BooleanDebugOption SyncIsoObject;

   public Network$Client(Network var1, IDebugOptionGroup var2) {
      super(var2, "Client");
      this.this$0 = var1;
      this.MainLoop = newDebugOnlyOption(this.Group, "MainLoop", true);
      this.UpdateZombiesFromPacket = newDebugOnlyOption(this.Group, "UpdateZombiesFromPacket", true);
      this.SyncIsoObject = newDebugOnlyOption(this.Group, "SyncIsoObject", true);
   }
}
