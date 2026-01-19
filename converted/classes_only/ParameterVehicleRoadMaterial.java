package zombie.audio.parameters;

import zombie.audio.FMODLocalParameter;
import zombie.audio.parameters.ParameterVehicleRoadMaterial.Material;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoObject;
import zombie.vehicles.BaseVehicle;

public final class ParameterVehicleRoadMaterial extends FMODLocalParameter {
   private final BaseVehicle vehicle;

   public ParameterVehicleRoadMaterial(BaseVehicle var1) {
      super("VehicleRoadMaterial");
      this.vehicle = var1;
   }

   public float calculateCurrentValue() {
      if (!this.vehicle.isEngineRunning()) {
         return Float.isNaN(this.getCurrentValue()) ? 0.0F : this.getCurrentValue();
      } else {
         return this.getMaterial().label;
      }
   }

   private Material getMaterial() {
      IsoGridSquare var1 = this.vehicle.getCurrentSquare();
      if (var1 == null) {
         return Material.Concrete;
      } else {
         IsoObject var2 = this.vehicle.getCurrentSquare().getFloor();
         if (var2 != null && var2.getSprite() != null && var2.getSprite().getName() != null) {
            String var3 = var2.getSprite().getName();
            if (var3.endsWith("blends_natural_01_5")
               || var3.endsWith("blends_natural_01_6")
               || var3.endsWith("blends_natural_01_7")
               || var3.endsWith("blends_natural_01_0")) {
               return Material.Sand;
            } else if (var3.endsWith("blends_natural_01_64")
               || var3.endsWith("blends_natural_01_69")
               || var3.endsWith("blends_natural_01_70")
               || var3.endsWith("blends_natural_01_71")) {
               return Material.Dirt;
            } else if (var3.startsWith("blends_natural_01")) {
               return Material.Grass;
            } else if (var3.endsWith("blends_street_01_48")
               || var3.endsWith("blends_street_01_53")
               || var3.endsWith("blends_street_01_54")
               || var3.endsWith("blends_street_01_55")) {
               return Material.Gravel;
            } else if (var3.startsWith("floors_interior_tilesandwood_01_")) {
               int var5 = Integer.parseInt(var3.replaceFirst("floors_interior_tilesandwood_01_", ""));
               return var5 > 40 && var5 < 48 ? Material.Wood : Material.Concrete;
            } else if (var3.startsWith("carpentry_02_")) {
               return Material.Wood;
            } else if (var3.contains("interior_carpet_")) {
               return Material.Carpet;
            } else {
               float var4 = var1.getPuddlesInGround();
               return var4 > 0.1 ? Material.Puddle : Material.Concrete;
            }
         } else {
            return Material.Concrete;
         }
      }
   }
}
