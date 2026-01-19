package zombie;

import zombie.SandboxOptions.BooleanSandboxOption;

public final class SandboxOptions$Map {
   public final BooleanSandboxOption AllowMiniMap;
   public final BooleanSandboxOption AllowWorldMap;
   public final BooleanSandboxOption MapAllKnown;

   SandboxOptions$Map(SandboxOptions var1) {
      this.this$0 = var1;
      this.AllowMiniMap = var1.newBooleanOption("Map.AllowMiniMap", false);
      this.AllowWorldMap = var1.newBooleanOption("Map.AllowWorldMap", true);
      this.MapAllKnown = var1.newBooleanOption("Map.MapAllKnown", false);
   }
}
