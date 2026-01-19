package zombie.iso.areas.isoregion;

import java.util.ArrayList;
import zombie.config.BooleanConfigOption;
import zombie.config.ConfigOption;

public class IsoRegionsRenderer$BooleanDebugOption extends BooleanConfigOption {
   private int index;
   private int zLevel = 0;

   public IsoRegionsRenderer$BooleanDebugOption(ArrayList<ConfigOption> var1, String var2, boolean var3, int var4) {
      super(var2, var3);
      this.index = var1.size();
      this.zLevel = var4;
      var1.add(this);
   }

   public IsoRegionsRenderer$BooleanDebugOption(ArrayList<ConfigOption> var1, String var2, boolean var3) {
      super(var2, var3);
      this.index = var1.size();
      var1.add(this);
   }

   public int getIndex() {
      return this.index;
   }
}
