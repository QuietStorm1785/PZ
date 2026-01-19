package zombie.randomizedWorld.randomizedVehicleStory;

import zombie.core.Rand;
import zombie.core.math.PZMath;
import zombie.inventory.InventoryItem;
import zombie.iso.IsoChunk;
import zombie.iso.IsoDirections;
import zombie.iso.IsoGridSquare;
import zombie.iso.Vector2;
import zombie.iso.IsoMetaGrid.Zone;
import zombie.randomizedWorld.randomizedVehicleStory.VehicleStorySpawner.Element;
import zombie.vehicles.BaseVehicle;
import zombie.vehicles.VehiclePart;

public final class RVSChangingTire extends RandomizedVehicleStoryBase {
   public RVSChangingTire() {
      this.name = "Changing Tire";
      this.minZoneWidth = 5;
      this.minZoneHeight = 5;
      this.setChance(3);
   }

   public void randomizeVehicleStory(Zone var1, IsoChunk var2) {
      float var3 = (float) (Math.PI / 6);
      this.callVehicleStorySpawner(var1, var2, Rand.Next(-var3, var3));
   }

   public boolean initVehicleStorySpawner(Zone var1, IsoChunk var2, boolean var3) {
      VehicleStorySpawner var4 = VehicleStorySpawner.getInstance();
      var4.clear();
      boolean var5 = Rand.NextBool(2);
      if (var3) {
         var5 = true;
      }

      int var6 = var5 ? 1 : -1;
      Vector2 var7 = IsoDirections.N.ToVector();
      var4.addElement("vehicle1", var6 * -1.5F, 0.0F, var7.getDirection(), 2.0F, 5.0F);
      var4.addElement("tire1", var6 * 0.0F, 0.0F, 0.0F, 1.0F, 1.0F);
      var4.addElement("tool1", var6 * 0.8F, -0.2F, 0.0F, 1.0F, 1.0F);
      var4.addElement("tool2", var6 * 1.2F, 0.2F, 0.0F, 1.0F, 1.0F);
      var4.addElement("tire2", var6 * 2.0F, 0.0F, 0.0F, 1.0F, 1.0F);
      var4.setParameter("zone", var1);
      var4.setParameter("removeRightWheel", var5);
      return true;
   }

   public void spawnElement(VehicleStorySpawner var1, Element var2) {
      IsoGridSquare var3 = var2.square;
      if (var3 != null) {
         float var4 = PZMath.max(var2.position.x - var3.x, 0.001F);
         float var5 = PZMath.max(var2.position.y - var3.y, 0.001F);
         float var6 = 0.0F;
         float var7 = var2.z;
         Zone var8 = (Zone)var1.getParameter("zone", Zone.class);
         boolean var9 = var1.getParameterBoolean("removeRightWheel");
         BaseVehicle var10 = (BaseVehicle)var1.getParameter("vehicle1", BaseVehicle.class);
         String var11 = var2.id;
         switch (var11) {
            case "tire1":
               if (var10 != null) {
                  InventoryItem var16 = var3.AddWorldInventoryItem("Base.ModernTire" + var10.getScript().getMechanicType(), var4, var5, var6);
                  if (var16 != null) {
                     var16.setItemCapacity(var16.getMaxCapacity());
                  }

                  this.addBloodSplat(var3, Rand.Next(10, 20));
               }
               break;
            case "tire2":
               if (var10 != null) {
                  InventoryItem var15 = var3.AddWorldInventoryItem("Base.OldTire" + var10.getScript().getMechanicType(), var4, var5, var6);
                  if (var15 != null) {
                     var15.setCondition(0);
                  }
               }
               break;
            case "tool1":
               var3.AddWorldInventoryItem("Base.LugWrench", var4, var5, var6);
               break;
            case "tool2":
               var3.AddWorldInventoryItem("Base.Jack", var4, var5, var6);
               break;
            case "vehicle1":
               var10 = this.addVehicle(var8, var2.position.x, var2.position.y, var7, var2.direction, "good", null, null, null);
               if (var10 != null) {
                  var10.setGeneralPartCondition(0.7F, 40.0F);
                  var10.setRust(0.0F);
                  VehiclePart var13 = var10.getPartById(var9 ? "TireRearRight" : "TireRearLeft");
                  var10.setTireRemoved(var13.getWheelIndex(), true);
                  var13.setModelVisible("InflatedTirePlusWheel", false);
                  var13.setInventoryItem(null);
                  this.addZombiesOnVehicle(2, null, null, var10);
                  var1.setParameter("vehicle1", var10);
               }
         }
      }
   }
}
