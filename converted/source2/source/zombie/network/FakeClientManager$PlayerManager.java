package zombie.network;

import java.nio.ByteBuffer;
import java.util.HashMap;
import zombie.network.FakeClientManager.Player;
import zombie.network.FakeClientManager.PlayerManager.RemotePlayer;
import zombie.network.packets.PlayerPacket;

class FakeClientManager$PlayerManager {
   private Player player = null;
   private final PlayerPacket playerPacket = new PlayerPacket();
   public final HashMap<Integer, RemotePlayer> players = new HashMap<>();

   public FakeClientManager$PlayerManager(Player var1) {
      this.player = var1;
   }

   private void parsePlayer(ByteBuffer var1) {
      PlayerPacket var2 = this.playerPacket;
      var2.parse(var1, null);
      synchronized (this.players) {
         RemotePlayer var4 = this.players.get(var2.id);
         if (var4 == null) {
            var4 = new RemotePlayer(this, var2.id);
            this.players.put(Integer.valueOf(var2.id), var4);
            FakeClientManager.trace(this.player.movement.id, String.format("New player %s", var4.OnlineID));
         }

         var4.playerPacket.copy(var2);
         var4.x = var2.realx;
         var4.y = var2.realy;
         var4.z = var2.realz;
      }
   }

   private void parsePlayerTimeout(ByteBuffer var1) {
      short var2 = var1.getShort();
      synchronized (this.players) {
         this.players.remove(var2);
      }

      FakeClientManager.trace(this.player.movement.id, String.format("Remove player %s", var2));
   }
}
