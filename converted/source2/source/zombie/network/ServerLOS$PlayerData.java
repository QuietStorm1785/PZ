package zombie.network;

import zombie.characters.IsoPlayer;
import zombie.network.ServerLOS.UpdateStatus;

class ServerLOS$PlayerData {
   public IsoPlayer player;
   public UpdateStatus status;
   public int px;
   public int py;
   public int pz;
   public boolean[][][] visible;

   public ServerLOS$PlayerData(ServerLOS var1, IsoPlayer var2) {
      this.this$0 = var1;
      this.status = UpdateStatus.NeverDone;
      this.visible = new boolean[100][100][8];
      this.player = var2;
   }
}
