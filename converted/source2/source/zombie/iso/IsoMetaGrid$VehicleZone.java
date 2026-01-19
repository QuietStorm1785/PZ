package zombie.iso;

import se.krka.kahlua.vm.KahluaTable;
import zombie.iso.IsoMetaGrid.Zone;

public final class IsoMetaGrid$VehicleZone extends Zone {
   public static final short VZF_FaceDirection = 1;
   public IsoDirections dir = IsoDirections.Max;
   public short flags = 0;

   public IsoMetaGrid$VehicleZone(String var1, String var2, int var3, int var4, int var5, int var6, int var7, KahluaTable var8) {
      super(var1, var2, var3, var4, var5, var6, var7);
      if (var8 != null) {
         Object var9 = var8.rawget("Direction");
         if (var9 instanceof String) {
            this.dir = IsoDirections.valueOf((String)var9);
         }

         var9 = var8.rawget("FaceDirection");
         if (var9 == Boolean.TRUE) {
            this.flags = (short)(this.flags | 1);
         }
      }
   }

   public boolean isFaceDirection() {
      return (this.flags & 1) != 0;
   }
}
