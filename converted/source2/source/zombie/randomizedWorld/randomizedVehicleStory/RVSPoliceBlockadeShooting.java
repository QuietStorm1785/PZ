package zombie.randomizedWorld.randomizedVehicleStory;

import zombie.core.Rand;
import zombie.iso.IsoCell;
import zombie.iso.IsoChunk;
import zombie.iso.IsoDirections;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoObject;
import zombie.iso.Vector2;
import zombie.iso.IsoMetaGrid.Zone;
import zombie.randomizedWorld.randomizedVehicleStory.VehicleStorySpawner.Element;
import zombie.vehicles.BaseVehicle;
import zombie.vehicles.VehiclePart;

public final class RVSPoliceBlockadeShooting extends RandomizedVehicleStoryBase {
   public RVSPoliceBlockadeShooting() {
      this.name = "Police Blockade Shooting";
      this.minZoneWidth = 8;
      this.minZoneHeight = 8;
      this.setChance(1);
      this.setMaximumDays(30);
   }

   public boolean isValid(Zone var1, IsoChunk var2, boolean var3) {
      boolean var4 = super.isValid(var1, var2, var3);
      return !var4 ? false : var1.isRectangle();
   }

   public void randomizeVehicleStory(Zone var1, IsoChunk var2) {
      this.callVehicleStorySpawner(var1, var2, 0.0F);
   }

   public boolean initVehicleStorySpawner(Zone var1, IsoChunk var2, boolean var3) {
      VehicleStorySpawner var4 = VehicleStorySpawner.getInstance();
      var4.clear();
      float var5 = (float) (Math.PI / 18);
      if (var3) {
         var5 = 0.0F;
      }

      float var6 = 1.5F;
      float var7 = 1.0F;
      if (this.zoneWidth >= 10) {
         var6 = 2.5F;
         var7 = 0.0F;
      }

      boolean var8 = Rand.NextBool(2);
      if (var3) {
         var8 = true;
      }

      IsoDirections var9 = Rand.NextBool(2) ? IsoDirections.W : IsoDirections.E;
      Vector2 var10 = var9.ToVector();
      var10.rotate(Rand.Next(-var5, var5));
      var4.addElement("vehicle1", -var6, var7, var10.getDirection(), 2.0F, 5.0F);
      var10 = var9.RotLeft(4).ToVector();
      var10.rotate(Rand.Next(-var5, var5));
      var4.addElement("vehicle2", var6, -var7, var10.getDirection(), 2.0F, 5.0F);
      var4.addElement("barricade", 0.0F, var8 ? -var7 - 2.5F : var7 + 2.5F, IsoDirections.N.ToVector().getDirection(), this.zoneWidth, 1.0F);
      int var11 = Rand.Next(7, 15);

      for (int var12 = 0; var12 < var11; var12++) {
         var4.addElement(
            "corpse",
            Rand.Next(-this.zoneWidth / 2.0F + 1.0F, this.zoneWidth / 2.0F - 1.0F),
            var8 ? Rand.Next(-7, -4) - var7 : Rand.Next(5, 8) + var7,
            IsoDirections.getRandom().ToVector().getDirection(),
            1.0F,
            2.0F
         );
      }

      String var14 = "Base.CarLightsPolice";
      if (Rand.NextBool(3)) {
         var14 = "Base.PickUpVanLightsPolice";
      }

      var4.setParameter("zone", var1);
      var4.setParameter("script", var14);
      return true;
   }

   public void spawnElement(VehicleStorySpawner var1, Element var2) {
      IsoGridSquare var3 = var2.square;
      if (var3 != null) {
         float var4 = var2.z;
         Zone var5 = (Zone)var1.getParameter("zone", Zone.class);
         String var6 = var1.getParameterString("script");
         String var7 = var2.id;
         switch (var7) {
            case "barricade":
               if (this.horizontalZone) {
                  int var15 = (int)(var2.position.y - var2.width / 2.0F);
                  int var19 = (int)(var2.position.y + var2.width / 2.0F) - 1;
                  int var22 = (int)var2.position.x;

                  for (int var12 = var15; var12 <= var19; var12++) {
                     IsoGridSquare var13 = IsoCell.getInstance().getGridSquare(var22, var12, var5.z);
                     if (var13 != null) {
                        if (var12 != var15 && var12 != var19) {
                           var13.AddTileObject(IsoObject.getNew(var13, "construction_01_9", null, false));
                        } else {
                           var13.AddTileObject(IsoObject.getNew(var13, "street_decoration_01_26", null, false));
                        }
                     }
                  }
               } else {
                  int var16 = (int)(var2.position.x - var2.width / 2.0F);
                  int var20 = (int)(var2.position.x + var2.width / 2.0F) - 1;
                  int var23 = (int)var2.position.y;

                  for (int var24 = var16; var24 <= var20; var24++) {
                     IsoGridSquare var25 = IsoCell.getInstance().getGridSquare(var24, var23, var5.z);
                     if (var25 != null) {
                        if (var24 != var16 && var24 != var20) {
                           var25.AddTileObject(IsoObject.getNew(var25, "construction_01_8", null, false));
                        } else {
                           var25.AddTileObject(IsoObject.getNew(var25, "street_decoration_01_26", null, false));
                        }
                     }
                  }
               }
               break;
            case "corpse":
               BaseVehicle var14 = (BaseVehicle)var1.getParameter("vehicle1", BaseVehicle.class);
               if (var14 != null) {
                  createRandomDeadBody(var2.position.x, var2.position.y, var5.z, var2.direction, false, 10, 10, null);
                  IsoDirections var18 = this.horizontalZone
                     ? (var2.position.x < var14.x ? IsoDirections.W : IsoDirections.E)
                     : (var2.position.y < var14.y ? IsoDirections.N : IsoDirections.S);
                  float var21 = var18.ToVector().getDirection();
                  this.addTrailOfBlood(var2.position.x, var2.position.y, var2.z, var21, 5);
               }
               break;
            case "vehicle1":
            case "vehicle2":
               BaseVehicle var9 = this.addVehicle(var5, var2.position.x, var2.position.y, var4, var2.direction, null, var6, null, null);
               if (var9 != null) {
                  var1.setParameter(var2.id, var9);
                  if (Rand.NextBool(3)) {
                     var9.setHeadlightsOn(true);
                     var9.setLightbarLightsMode(2);
                     VehiclePart var10 = var9.getBattery();
                     if (var10 != null) {
                        var10.setLastUpdated(0.0F);
                     }
                  }

                  String var17 = "PoliceRiot";
                  Integer var11 = 0;
                  this.addZombiesOnVehicle(Rand.Next(2, 4), var17, var11, var9);
               }
         }
      }
   }
}
