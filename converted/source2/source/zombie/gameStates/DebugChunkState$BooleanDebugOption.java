package zombie.gameStates;

import zombie.config.BooleanConfigOption;

public class DebugChunkState$BooleanDebugOption extends BooleanConfigOption {
   public DebugChunkState$BooleanDebugOption(DebugChunkState var1, String var2, boolean var3) {
      super(var2, var3);
      this.this$0 = var1;
      var1.options.add(this);
   }
}
