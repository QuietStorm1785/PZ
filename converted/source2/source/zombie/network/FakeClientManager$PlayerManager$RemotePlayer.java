package zombie.network;

import zombie.network.FakeClientManager.PlayerManager;
import zombie.network.packets.PlayerPacket;

class FakeClientManager$PlayerManager$RemotePlayer {
   public float x;
   public float y;
   public float z;
   public short OnlineID;
   public PlayerPacket playerPacket;

   public FakeClientManager$PlayerManager$RemotePlayer(PlayerManager var1, short var2) {
      this.this$0 = var1;
      this.playerPacket = null;
      this.playerPacket = new PlayerPacket();
      this.playerPacket.id = var2;
      this.OnlineID = var2;
   }
}
