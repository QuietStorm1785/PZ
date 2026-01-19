package zombie.iso.objects;

import se.krka.kahlua.vm.KahluaTable;
import zombie.iso.IsoDirections;
import zombie.iso.IsoMetaGrid.Zone;

public final class IsoMannequin$MannequinZone extends Zone {
   public int bFemale = -1;
   public IsoDirections dir = IsoDirections.Max;
   public String mannequinScript = null;
   public String pose = null;
   public String skin = null;
   public String outfit = null;

   public IsoMannequin$MannequinZone(String var1, String var2, int var3, int var4, int var5, int var6, int var7, KahluaTable var8) {
      super(var1, var2, var3, var4, var5, var6, var7);
      if (var8 != null) {
         Object var9 = var8.rawget("Female");
         if (var9 instanceof Boolean) {
            this.bFemale = var9 == Boolean.TRUE ? 1 : 0;
         }

         var9 = var8.rawget("Direction");
         if (var9 instanceof String) {
            this.dir = IsoDirections.valueOf((String)var9);
         }

         var9 = var8.rawget("Outfit");
         if (var9 instanceof String) {
            this.outfit = (String)var9;
         }

         var9 = var8.rawget("Script");
         if (var9 instanceof String) {
            this.mannequinScript = (String)var9;
         }

         var9 = var8.rawget("Skin");
         if (var9 instanceof String) {
            this.skin = (String)var9;
         }

         var9 = var8.rawget("Pose");
         if (var9 instanceof String) {
            this.pose = (String)var9;
         }
      }
   }
}
