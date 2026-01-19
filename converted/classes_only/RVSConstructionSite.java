package zombie.randomizedWorld.randomizedVehicleStory;

import java.util.ArrayList;
import zombie.core.Rand;
import zombie.core.math.PZMath;
import zombie.iso.IsoChunk;
import zombie.iso.IsoDirections;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoObject;
import zombie.iso.Vector2;
import zombie.iso.IsoMetaGrid.Zone;
import zombie.randomizedWorld.randomizedVehicleStory.VehicleStorySpawner.Element;
import zombie.vehicles.BaseVehicle;

public final class RVSConstructionSite extends RandomizedVehicleStoryBase {
   private ArrayList<String> tools = null;

   public RVSConstructionSite() {
      this.name = "Construction Site";
      this.minZoneWidth = 6;
      this.minZoneHeight = 6;
      this.setChance(3);
      this.tools = new ArrayList<>();
      this.tools.add("Base.PickAxe");
      this.tools.add("Base.Shovel");
      this.tools.add("Base.Shovel2");
      this.tools.add("Base.Hammer");
      this.tools.add("Base.LeadPipe");
      this.tools.add("Base.PipeWrench");
      this.tools.add("Base.Sledgehammer");
      this.tools.add("Base.Sledgehammer2");
   }

   public void randomizeVehicleStory(Zone var1, IsoChunk var2) {
      this.callVehicleStorySpawner(var1, var2, 0.0F);
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
      float var8 = (float) (Math.PI / 6);
      if (var3) {
         var8 = 0.0F;
      }

      var7.rotate(Rand.Next(-var8, var8));
      var4.addElement("vehicle1", -var6 * 2.0F, 0.0F, var7.getDirection(), 2.0F, 5.0F);
      float var9 = 0.0F;
      var4.addElement("manhole", var6 * 1.5F, 1.5F, var9, 3.0F, 3.0F);
      int var10 = Rand.Next(0, 3);

      for (int var11 = 0; var11 < var10; var11++) {
         var9 = 0.0F;
         var4.addElement("tool", var6 * Rand.Next(0.0F, 3.0F), -Rand.Next(0.7F, 2.3F), var9, 1.0F, 1.0F);
      }

      var4.setParameter("zone", var1);
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
         BaseVehicle var9 = (BaseVehicle)var1.getParameter("vehicle1", BaseVehicle.class);
         String var10 = var2.id;
         switch (var10) {
            case "manhole":
               var3.AddTileObject(IsoObject.getNew(var3, "street_decoration_01_15", null, false));
               IsoGridSquare var14 = var3.getAdjacentSquare(IsoDirections.E);
               if (var14 != null) {
                  var14.AddTileObject(IsoObject.getNew(var14, "street_decoration_01_26", null, false));
               }

               var14 = var3.getAdjacentSquare(IsoDirections.W);
               if (var14 != null) {
                  var14.AddTileObject(IsoObject.getNew(var14, "street_decoration_01_26", null, false));
               }

               var14 = var3.getAdjacentSquare(IsoDirections.S);
               if (var14 != null) {
                  var14.AddTileObject(IsoObject.getNew(var14, "street_decoration_01_26", null, false));
               }

               var14 = var3.getAdjacentSquare(IsoDirections.N);
               if (var14 != null) {
                  var14.AddTileObject(IsoObject.getNew(var14, "street_decoration_01_26", null, false));
               }
               break;
            case "tool":
               String var12 = this.tools.get(Rand.Next(this.tools.size()));
               var3.AddWorldInventoryItem(var12, var4, var5, var6);
               break;
            case "vehicle1":
               var9 = this.addVehicle(var8, var2.position.x, var2.position.y, var7, var2.direction, null, "Base.PickUpTruck", null, "ConstructionWorker");
               if (var9 != null) {
                  this.addZombiesOnVehicle(Rand.Next(2, 5), "ConstructionWorker", 0, var9);
                  this.addZombiesOnVehicle(1, "Foreman", 0, var9);
                  var1.setParameter("vehicle1", var9);
               }
         }
      }
   }
}
