package zombie.randomizedWorld.randomizedBuilding;

import zombie.core.Rand;
import zombie.inventory.ItemPickerJava;
import zombie.inventory.ItemPickerJava.ItemPickerRoom;
import zombie.iso.BuildingDef;
import zombie.iso.IsoCell;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoObject;
import zombie.iso.IsoWorld;
import zombie.iso.SpawnPoints;
import zombie.iso.objects.IsoBarricade;
import zombie.iso.objects.IsoDoor;
import zombie.iso.objects.IsoWindow;
import zombie.network.GameServer;

public final class RBSafehouse extends RandomizedBuildingBase {
   public void randomizeBuilding(BuildingDef var1) {
      var1.bAlarmed = false;
      var1.setHasBeenVisited(true);
      ItemPickerRoom var2 = (ItemPickerRoom)ItemPickerJava.rooms.get("SafehouseLoot");
      IsoCell var3 = IsoWorld.instance.CurrentCell;

      for (int var4 = var1.x - 1; var4 < var1.x2 + 1; var4++) {
         for (int var5 = var1.y - 1; var5 < var1.y2 + 1; var5++) {
            for (int var6 = 0; var6 < 8; var6++) {
               IsoGridSquare var7 = var3.getGridSquare(var4, var5, var6);
               if (var7 != null) {
                  for (int var8 = 0; var8 < var7.getObjects().size(); var8++) {
                     IsoObject var9 = (IsoObject)var7.getObjects().get(var8);
                     if (var9 instanceof IsoDoor && ((IsoDoor)var9).isBarricadeAllowed() && !SpawnPoints.instance.isSpawnBuilding(var1)) {
                        IsoGridSquare var10 = var7.getRoom() == null ? var7 : ((IsoDoor)var9).getOppositeSquare();
                        if (var10 != null && var10.getRoom() == null) {
                           boolean var11 = var10 != var7;
                           IsoBarricade var12 = IsoBarricade.AddBarricadeToObject((IsoDoor)var9, var11);
                           if (var12 != null) {
                              int var13 = Rand.Next(1, 4);

                              for (int var14 = 0; var14 < var13; var14++) {
                                 var12.addPlank(null, null);
                              }

                              if (GameServer.bServer) {
                                 var12.transmitCompleteItemToClients();
                              }
                           }
                        }
                     }

                     if (var9 instanceof IsoWindow) {
                        IsoGridSquare var15 = var7.getRoom() == null ? var7 : ((IsoWindow)var9).getOppositeSquare();
                        if (((IsoWindow)var9).isBarricadeAllowed() && var6 == 0 && var15 != null && var15.getRoom() == null) {
                           boolean var16 = var15 != var7;
                           IsoBarricade var17 = IsoBarricade.AddBarricadeToObject((IsoWindow)var9, var16);
                           if (var17 != null) {
                              int var18 = Rand.Next(1, 4);

                              for (int var19 = 0; var19 < var18; var19++) {
                                 var17.addPlank(null, null);
                              }

                              if (GameServer.bServer) {
                                 var17.transmitCompleteItemToClients();
                              }
                           }
                        } else {
                           ((IsoWindow)var9).addSheet(null);
                           ((IsoWindow)var9).HasCurtains().ToggleDoor(null);
                        }
                     }

                     if (var9.getContainer() != null
                        && var7.getRoom() != null
                        && var7.getRoom().getBuilding().getDef() == var1
                        && Rand.Next(100) <= 70
                        && var7.getRoom().getName() != null
                        && var2.Containers.containsKey(var9.getContainer().getType())) {
                        var9.getContainer().clear();
                        ItemPickerJava.fillContainerType(var2, var9.getContainer(), "", null);
                        ItemPickerJava.updateOverlaySprite(var9);
                        var9.getContainer().setExplored(true);
                     }
                  }
               }
            }
         }
      }

      var1.setAllExplored(true);
      var1.bAlarmed = false;
      this.addZombies(var1);
   }

   private void addZombies(BuildingDef var1) {
      this.addZombies(var1, 0, null, null, null);
      if (Rand.Next(5) == 0) {
         this.addZombies(var1, 1, "Survivalist", null, null);
      }

      if (Rand.Next(100) <= 60) {
         RandomizedBuildingBase.createRandomDeadBody(this.getLivingRoomOrKitchen(var1), Rand.Next(3, 7));
      }

      if (Rand.Next(100) <= 60) {
         RandomizedBuildingBase.createRandomDeadBody(this.getLivingRoomOrKitchen(var1), Rand.Next(3, 7));
      }
   }

   public boolean isValid(BuildingDef var1, boolean var2) {
      if (!super.isValid(var1, var2)) {
         return false;
      } else {
         return var1.getRooms().size() > 20 ? false : !SpawnPoints.instance.isSpawnBuilding(var1);
      }
   }

   public RBSafehouse() {
      this.name = "Safehouse";
      this.setChance(10);
   }
}
