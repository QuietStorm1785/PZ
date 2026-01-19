package zombie.vehicles;

import zombie.core.math.PZMath;
import zombie.scripting.ScriptParser;
import zombie.scripting.ScriptParser.Block;
import zombie.scripting.ScriptParser.Value;
import zombie.scripting.objects.BaseScriptObject;

public class VehicleEngineRPM extends BaseScriptObject {
   public static final int MAX_GEARS = 8;
   private static final int VERSION1 = 1;
   private static final int VERSION = 1;
   private String m_name;
   public final EngineRPMData[] m_rpmData = new EngineRPMData[8];

   public String getName() {
      return this.m_name;
   }

   public void Load(String var1, String var2) throws RuntimeException {
      this.m_name = var1;
      int var3 = -1;
      Block var4 = ScriptParser.parse(var2);
      var4 = (Block)var4.children.get(0);

      for (Value var6 : var4.values) {
         String var7 = var6.getKey().trim();
         String var8 = var6.getValue().trim();
         if ("VERSION".equals(var7)) {
            var3 = PZMath.tryParseInt(var8, -1);
            if (var3 < 0 || var3 > 1) {
               throw new RuntimeException(String.format("unknown vehicleEngineRPM VERSION \"%s\"", var8));
            }
         }
      }

      if (var3 == -1) {
         throw new RuntimeException(String.format("unknown vehicleEngineRPM VERSION \"%s\"", var4.type));
      } else {
         int var10 = 0;

         for (Block var12 : var4.children) {
            if (!"data".equals(var12.type)) {
               throw new RuntimeException(String.format("unknown block vehicleEngineRPM.%s", var12.type));
            }

            if (var10 == 8) {
               throw new RuntimeException(String.format("too many vehicleEngineRPM.data blocks, max is %d", 8));
            }

            this.m_rpmData[var10] = new EngineRPMData();
            this.LoadData(var12, this.m_rpmData[var10]);
            var10++;
         }
      }
   }

   private void LoadData(Block var1, EngineRPMData var2) {
      for (Value var4 : var1.values) {
         String var5 = var4.getKey().trim();
         String var6 = var4.getValue().trim();
         if ("afterGearChange".equals(var5)) {
            var2.afterGearChange = PZMath.tryParseFloat(var6, 0.0F);
         } else {
            if (!"gearChange".equals(var5)) {
               throw new RuntimeException(String.format("unknown value vehicleEngineRPM.data.%s", var4.string));
            }

            var2.gearChange = PZMath.tryParseFloat(var6, 0.0F);
         }
      }

      for (Block var8 : var1.children) {
         if (!"xxx".equals(var8.type)) {
            throw new RuntimeException(String.format("unknown block vehicleEngineRPM.data.%s", var8.type));
         }
      }
   }

   public void reset() {
      for (int var1 = 0; var1 < this.m_rpmData.length; var1++) {
         if (this.m_rpmData[var1] != null) {
            this.m_rpmData[var1].reset();
         }
      }
   }
}
