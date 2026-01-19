package zombie.randomizedWorld.randomizedVehicleStory;

import java.util.ArrayList;
import zombie.characters.IsoZombie;
import zombie.characters.BodyDamage.BodyPartType;
import zombie.core.Rand;
import zombie.iso.IsoChunk;
import zombie.iso.IsoDirections;
import zombie.iso.IsoGridSquare;
import zombie.iso.Vector2;
import zombie.iso.IsoMetaGrid.Zone;
import zombie.randomizedWorld.randomizedVehicleStory.VehicleStorySpawner.Element;
import zombie.vehicles.BaseVehicle;

public final class RVSAmbulanceCrash extends RandomizedVehicleStoryBase {
   public RVSAmbulanceCrash() {
      this.name = "Ambulance Crash";
      this.minZoneWidth = 5;
      this.minZoneHeight = 7;
      this.setChance(5);
   }

   public void randomizeVehicleStory(Zone var1, IsoChunk var2) {
      this.callVehicleStorySpawner(var1, var2, 0.0F);
   }

   public boolean initVehicleStorySpawner(Zone var1, IsoChunk var2, boolean var3) {
      VehicleStorySpawner var4 = VehicleStorySpawner.getInstance();
      var4.clear();
      float var5 = (float) (Math.PI / 6);
      if (var3) {
         var5 = 0.0F;
      }

      Vector2 var6 = IsoDirections.N.ToVector();
      var6.rotate(Rand.Next(-var5, var5));
      var4.addElement("vehicle1", 0.0F, 1.0F, var6.getDirection(), 2.0F, 5.0F);
      boolean var7 = Rand.NextBool(2);
      var6 = var7 ? IsoDirections.E.ToVector() : IsoDirections.W.ToVector();
      var6.rotate(Rand.Next(-var5, var5));
      var4.addElement("vehicle2", 0.0F, -2.5F, var6.getDirection(), 2.0F, 5.0F);
      var4.setParameter("zone", var1);
      return true;
   }

   public void spawnElement(VehicleStorySpawner var1, Element var2) {
      IsoGridSquare var3 = var2.square;
      if (var3 != null) {
         float var4 = var2.z;
         Zone var5 = (Zone)var1.getParameter("zone", Zone.class);
         String var6 = var2.id;
         switch (var6) {
            case "vehicle1":
               BaseVehicle var12 = this.addVehicle(var5, var2.position.x, var2.position.y, var4, var2.direction, null, "Base.VanAmbulance", null, null);
               if (var12 != null) {
                  this.addZombiesOnVehicle(Rand.Next(1, 3), "AmbulanceDriver", null, var12);
                  ArrayList var9 = this.addZombiesOnVehicle(Rand.Next(1, 3), "HospitalPatient", null, var12);

                  for (int var10 = 0; var10 < var9.size(); var10++) {
                     for (int var11 = 0; var11 < 7; var11++) {
                        if (Rand.NextBool(2)) {
                           ((IsoZombie)var9.get(var10)).addVisualBandage(BodyPartType.getRandom(), true);
                        }
                     }
                  }
               }
               break;
            case "vehicle2":
               BaseVehicle var8 = this.addVehicle(var5, var2.position.x, var2.position.y, var4, var2.direction, "bad", null, null, null);
               if (var8 == null) {
               }
         }
      }
   }
}
