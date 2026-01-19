package zombie.network;

import java.util.Comparator;
import zombie.core.raknet.UdpConnection;
import zombie.iso.IsoUtils;
import zombie.iso.Vector2;
import zombie.network.ServerMap.ServerCell;

class ServerMap$DistToCellComparator implements Comparator<ServerCell> {
   private Vector2[] pos = new Vector2[1024];
   private int posCount;

   public ServerMap$DistToCellComparator() {
      for (int var1 = 0; var1 < this.pos.length; var1++) {
         this.pos[var1] = new Vector2();
      }
   }

   public void init() {
      this.posCount = 0;

      for (int var1 = 0; var1 < GameServer.udpEngine.connections.size(); var1++) {
         UdpConnection var2 = (UdpConnection)GameServer.udpEngine.connections.get(var1);
         if (var2.isFullyConnected()) {
            for (int var3 = 0; var3 < 4; var3++) {
               if (var2.players[var3] != null) {
                  this.pos[this.posCount].set(var2.players[var3].x, var2.players[var3].y);
                  this.posCount++;
               }
            }
         }
      }
   }

   public int compare(ServerCell var1, ServerCell var2) {
      float var3 = Float.MAX_VALUE;
      float var4 = Float.MAX_VALUE;

      for (int var5 = 0; var5 < this.posCount; var5++) {
         float var6 = this.pos[var5].x;
         float var7 = this.pos[var5].y;
         var3 = Math.min(var3, this.distToCell(var6, var7, var1));
         var4 = Math.min(var4, this.distToCell(var6, var7, var2));
      }

      if (var3 < var4) {
         return -1;
      } else {
         return var3 > var4 ? 1 : 0;
      }
   }

   private float distToCell(float var1, float var2, ServerCell var3) {
      int var4 = var3.WX * 50;
      int var5 = var3.WY * 50;
      int var6 = var4 + 50;
      int var7 = var5 + 50;
      float var8 = var1;
      float var9 = var2;
      if (var1 < var4) {
         var8 = var4;
      } else if (var1 > var6) {
         var8 = var6;
      }

      if (var2 < var5) {
         var9 = var5;
      } else if (var2 > var7) {
         var9 = var7;
      }

      return IsoUtils.DistanceToSquared(var1, var2, var8, var9);
   }
}
