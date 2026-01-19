package zombie.randomizedWorld.randomizedDeadSurvivor;

import zombie.VirtualZombieManager;
import zombie.ZombieSpawnRecorder;
import zombie.characters.IsoZombie;
import zombie.core.Rand;
import zombie.iso.BuildingDef;
import zombie.iso.IsoDirections;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoWorld;
import zombie.iso.RoomDef;
import zombie.iso.areas.IsoRoom;
import zombie.iso.objects.IsoBarricade;
import zombie.iso.objects.IsoDeadBody;
import zombie.iso.objects.IsoDoor;
import zombie.network.GameServer;

public final class RDSZombieLockedBathroom extends RandomizedDeadSurvivorBase {
   public void randomizeDeadSurvivor(BuildingDef var1) {
      IsoDeadBody var2 = null;

      for (int var3 = 0; var3 < var1.rooms.size(); var3++) {
         RoomDef var4 = (RoomDef)var1.rooms.get(var3);
         IsoGridSquare var5 = null;
         if ("bathroom".equals(var4.name)) {
            if (IsoWorld.getZombiesEnabled()) {
               IsoGridSquare var6 = IsoWorld.instance.CurrentCell.getGridSquare(var4.getX(), var4.getY(), var4.getZ());
               if (var6 != null && var6.getRoom() != null) {
                  IsoRoom var7 = var6.getRoom();
                  var6 = var7.getRandomFreeSquare();
                  if (var6 != null) {
                     VirtualZombieManager.instance.choices.clear();
                     VirtualZombieManager.instance.choices.add(var6);
                     IsoZombie var8 = VirtualZombieManager.instance.createRealZombieAlways(IsoDirections.fromIndex(Rand.Next(8)).index(), false);
                     ZombieSpawnRecorder.instance.record(var8, this.getClass().getSimpleName());
                  }
               }
            }

            for (int var12 = var4.x - 1; var12 < var4.x2 + 1; var12++) {
               for (int var13 = var4.y - 1; var13 < var4.y2 + 1; var13++) {
                  var5 = IsoWorld.instance.getCell().getGridSquare(var12, var13, var4.getZ());
                  if (var5 != null) {
                     IsoDoor var14 = var5.getIsoDoor();
                     if (var14 != null && this.isDoorToRoom(var14, var4)) {
                        if (var14.IsOpen()) {
                           var14.ToggleDoor(null);
                        }

                        IsoBarricade var9 = IsoBarricade.AddBarricadeToObject(var14, var5.getRoom().def == var4);
                        if (var9 != null) {
                           var9.addPlank(null, null);
                           if (GameServer.bServer) {
                              var9.transmitCompleteItemToClients();
                           }
                        }

                        var2 = this.addDeadBodyTheOtherSide(var14);
                        break;
                     }
                  }
               }

               if (var2 != null) {
                  break;
               }
            }

            if (var2 != null) {
               var2.setPrimaryHandItem(super.addWeapon("Base.Pistol", true));
            }

            return;
         }
      }
   }

   private boolean isDoorToRoom(IsoDoor var1, RoomDef var2) {
      if (var1 != null && var2 != null) {
         IsoGridSquare var3 = var1.getSquare();
         IsoGridSquare var4 = var1.getOppositeSquare();
         return var3 != null && var4 != null ? var3.getRoomID() == var2.ID != (var4.getRoomID() == var2.ID) : false;
      } else {
         return false;
      }
   }

   private boolean checkIsBathroom(IsoGridSquare var1) {
      return var1.getRoom() != null && "bathroom".equals(var1.getRoom().getName());
   }

   private IsoDeadBody addDeadBodyTheOtherSide(IsoDoor var1) {
      Object var2 = null;
      if (var1.north) {
         var2 = IsoWorld.instance.getCell().getGridSquare(var1.getX(), var1.getY(), var1.getZ());
         if (this.checkIsBathroom((IsoGridSquare)var2)) {
            var2 = IsoWorld.instance.getCell().getGridSquare(var1.getX(), var1.getY() - 1.0F, var1.getZ());
         }
      } else {
         var2 = IsoWorld.instance.getCell().getGridSquare(var1.getX(), var1.getY(), var1.getZ());
         if (this.checkIsBathroom((IsoGridSquare)var2)) {
            var2 = IsoWorld.instance.getCell().getGridSquare(var1.getX() - 1.0F, var1.getY(), var1.getZ());
         }
      }

      return RandomizedDeadSurvivorBase.createRandomDeadBody(var2.getX(), var2.getY(), var2.getZ(), null, Rand.Next(5, 10));
   }

   public RDSZombieLockedBathroom() {
      this.name = "Locked in Bathroom";
      this.setChance(5);
   }
}
