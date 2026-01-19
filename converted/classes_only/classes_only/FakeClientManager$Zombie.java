package zombie.network;

import zombie.core.Rand;
import zombie.iso.IsoDirections;
import zombie.network.NetworkVariables.WalkType;
import zombie.network.packets.ZombiePacket;

class FakeClientManager$Zombie {
   public long lastUpdate;
   public float x;
   public float y;
   public float z;
   public short OnlineID;
   public boolean localOwnership = false;
   public ZombiePacket zombiePacket = null;
   public IsoDirections dir = IsoDirections.N;
   public float health = 1.0F;
   public byte walkType = (byte)Rand.Next(WalkType.values().length);
   public float dropPositionX;
   public float dropPositionY;
   public boolean isMoving = false;

   public FakeClientManager$Zombie(short var1) {
      this.zombiePacket = new ZombiePacket();
      this.zombiePacket.id = var1;
      this.OnlineID = var1;
      this.localOwnership = false;
   }
}
