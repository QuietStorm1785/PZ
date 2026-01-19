package zombie.randomizedWorld.randomizedVehicleStory;

import java.util.ArrayList;
import zombie.core.Rand;
import zombie.core.math.PZMath;
import zombie.iso.IsoChunk;
import zombie.iso.IsoDirections;
import zombie.iso.IsoGridSquare;
import zombie.iso.Vector2;
import zombie.iso.IsoMetaGrid.Zone;
import zombie.randomizedWorld.randomizedVehicleStory.RVSUtilityVehicle.Params;
import zombie.randomizedWorld.randomizedVehicleStory.VehicleStorySpawner.Element;
import zombie.util.list.PZArrayUtil;
import zombie.vehicles.BaseVehicle;

public final class RVSUtilityVehicle extends RandomizedVehicleStoryBase {
   private ArrayList<String> tools = null;
   private ArrayList<String> carpenterTools = null;
   private Params params = new Params();

   public RVSUtilityVehicle() {
      this.name = "Utility Vehicle";
      this.minZoneWidth = 8;
      this.minZoneHeight = 9;
      this.setChance(7);
      this.tools = new ArrayList<>();
      this.tools.add("Base.PickAxe");
      this.tools.add("Base.Shovel");
      this.tools.add("Base.Shovel2");
      this.tools.add("Base.Hammer");
      this.tools.add("Base.LeadPipe");
      this.tools.add("Base.PipeWrench");
      this.tools.add("Base.Sledgehammer");
      this.tools.add("Base.Sledgehammer2");
      this.carpenterTools = new ArrayList<>();
      this.carpenterTools.add("Base.Hammer");
      this.carpenterTools.add("Base.NailsBox");
      this.carpenterTools.add("Base.Plank");
      this.carpenterTools.add("Base.Plank");
      this.carpenterTools.add("Base.Plank");
      this.carpenterTools.add("Base.Screwdriver");
      this.carpenterTools.add("Base.Saw");
      this.carpenterTools.add("Base.Saw");
      this.carpenterTools.add("Base.Woodglue");
   }

   public void randomizeVehicleStory(Zone var1, IsoChunk var2) {
      this.callVehicleStorySpawner(var1, var2, 0.0F);
   }

   public void doUtilityVehicle(
      Zone var1, IsoChunk var2, String var3, String var4, String var5, Integer var6, String var7, ArrayList<String> var8, int var9, boolean var10
   ) {
      this.params.zoneName = var3;
      this.params.scriptName = var4;
      this.params.outfits = var5;
      this.params.femaleChance = var6;
      this.params.vehicleDistrib = var7;
      this.params.items = var8;
      this.params.nbrOfItem = var9;
      this.params.addTrailer = var10;
   }

   public boolean initVehicleStorySpawner(Zone var1, IsoChunk var2, boolean var3) {
      int var4 = Rand.Next(0, 7);
      switch (var4) {
         case 0:
            this.doUtilityVehicle(var1, var2, null, "Base.PickUpTruck", "ConstructionWorker", 0, "ConstructionWorker", this.tools, Rand.Next(0, 3), true);
            break;
         case 1:
            this.doUtilityVehicle(var1, var2, "police", null, "Police", null, null, null, 0, false);
            break;
         case 2:
            this.doUtilityVehicle(var1, var2, "fire", null, "Fireman", null, null, null, 0, false);
            break;
         case 3:
            this.doUtilityVehicle(var1, var2, "ranger", null, "Ranger", null, null, null, 0, true);
            break;
         case 4:
            this.doUtilityVehicle(var1, var2, "mccoy", null, "McCoys", 0, "Carpenter", this.carpenterTools, Rand.Next(2, 6), true);
            break;
         case 5:
            this.doUtilityVehicle(var1, var2, "postal", null, "Postal", null, null, null, 0, false);
            break;
         case 6:
            this.doUtilityVehicle(var1, var2, "fossoil", null, "Fossoil", null, null, null, 0, false);
      }

      VehicleStorySpawner var5 = VehicleStorySpawner.getInstance();
      var5.clear();
      Vector2 var6 = IsoDirections.N.ToVector();
      float var7 = (float) (Math.PI / 6);
      if (var3) {
         var7 = 0.0F;
      }

      var6.rotate(Rand.Next(-var7, var7));
      float var8 = -2.0F;
      byte var9 = 5;
      var5.addElement("vehicle1", 0.0F, var8, var6.getDirection(), 2.0F, var9);
      if (this.params.addTrailer && Rand.NextBool(7)) {
         byte var10 = 3;
         var5.addElement("trailer", 0.0F, var8 + var9 / 2.0F + 1.0F + var10 / 2.0F, var6.getDirection(), 2.0F, var10);
      }

      if (this.params.items != null) {
         for (int var11 = 0; var11 < this.params.nbrOfItem; var11++) {
            var5.addElement("tool", Rand.Next(-3.5F, 3.5F), Rand.Next(-3.5F, 3.5F), 0.0F, 1.0F, 1.0F);
         }
      }

      var5.setParameter("zone", var1);
      return true;
   }

   public void spawnElement(VehicleStorySpawner var1, Element var2) {
      IsoGridSquare var3 = var2.square;
      if (var3 != null) {
         float var4 = var2.z;
         Zone var5 = (Zone)var1.getParameter("zone", Zone.class);
         BaseVehicle var6 = (BaseVehicle)var1.getParameter("vehicle1", BaseVehicle.class);
         String var7 = var2.id;
         switch (var7) {
            case "tool":
               if (var6 != null) {
                  float var9 = PZMath.max(var2.position.x - var3.x, 0.001F);
                  float var10 = PZMath.max(var2.position.y - var3.y, 0.001F);
                  float var11 = 0.0F;
                  var3.AddWorldInventoryItem((String)PZArrayUtil.pickRandom(this.params.items), var9, var10, var11);
               }
               break;
            case "trailer":
               if (var6 != null) {
                  this.addTrailer(
                     var6, var5, var3.getChunk(), this.params.zoneName, this.params.vehicleDistrib, Rand.NextBool(1) ? "Base.Trailer" : "Base.TrailerCover"
                  );
               }
               break;
            case "vehicle1":
               var6 = this.addVehicle(
                  var5, var2.position.x, var2.position.y, var4, var2.direction, this.params.zoneName, this.params.scriptName, null, this.params.vehicleDistrib
               );
               if (var6 != null) {
                  this.addZombiesOnVehicle(Rand.Next(2, 5), this.params.outfits, this.params.femaleChance, var6);
               }
         }
      }
   }
}
