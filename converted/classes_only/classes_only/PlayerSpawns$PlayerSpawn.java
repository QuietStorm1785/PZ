package zombie.popman;

import zombie.iso.BuildingDef;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoWorld;
import zombie.iso.RoomDef;

class PlayerSpawns$PlayerSpawn {
   public int x;
   public int y;
   public long counter;
   public BuildingDef building;

   public PlayerSpawns$PlayerSpawn(int var1, int var2, int var3) {
      this.x = var1;
      this.y = var2;
      this.counter = -1L;
      RoomDef var4 = IsoWorld.instance.getMetaGrid().getRoomAt(var1, var2, var3);
      if (var4 != null) {
         this.building = var4.getBuilding();
      }
   }

   public boolean allowZombie(IsoGridSquare var1) {
      if (this.building == null) {
         return true;
      } else {
         return var1.getBuilding() != null && this.building == var1.getBuilding().getDef()
            ? false
            : var1.getX() < this.building.getX() - 15
               || var1.getX() >= this.building.getX2() + 15
               || var1.getY() < this.building.getY() - 15
               || var1.getY() >= this.building.getY2() + 15;
      }
   }
}
