package zombie.debug;

import zombie.debug.options.OptionGroup;

public final class DebugOptions$Checks extends OptionGroup {
   public final BooleanDebugOption BoundTextures = newDebugOnlyOption(this.Group, "BoundTextures", false);
   public final BooleanDebugOption SlowLuaEvents = newDebugOnlyOption(this.Group, "SlowLuaEvents", false);

   public DebugOptions$Checks() {
      super("Checks");
   }
}
