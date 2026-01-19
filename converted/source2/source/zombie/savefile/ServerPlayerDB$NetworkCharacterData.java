package zombie.savefile;

import java.nio.ByteBuffer;
import zombie.GameWindow;
import zombie.core.raknet.UdpConnection;
import zombie.core.znet.SteamUtils;
import zombie.network.GameServer;

final class ServerPlayerDB$NetworkCharacterData {
   byte[] buffer;
   String username;
   String steamid;
   int playerIndex;
   String playerName;
   float x;
   float y;
   float z;
   boolean isDead;
   int worldVersion;

   public ServerPlayerDB$NetworkCharacterData(ByteBuffer var1, UdpConnection var2) {
      this.playerIndex = var1.get();
      this.playerName = GameWindow.ReadStringUTF(var1);
      this.x = var1.getFloat();
      this.y = var1.getFloat();
      this.z = var1.getFloat();
      this.isDead = var1.get() == 1;
      this.worldVersion = var1.getInt();
      int var3 = var1.getInt();
      this.buffer = new byte[var3];
      var1.get(this.buffer);
      if (GameServer.bCoop && SteamUtils.isSteamModeEnabled()) {
         this.steamid = var2.idStr;
      } else {
         this.steamid = "";
      }

      this.username = var2.username;
   }
}
