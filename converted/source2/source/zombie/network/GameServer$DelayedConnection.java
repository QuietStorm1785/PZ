package zombie.network;

import zombie.core.raknet.UdpConnection;

class GameServer$DelayedConnection implements IZomboidPacket {
   public UdpConnection connection;
   public boolean connect;
   public String hostString;

   public GameServer$DelayedConnection(UdpConnection var1, boolean var2) {
      this.connection = var1;
      this.connect = var2;
      if (var2) {
         try {
            this.hostString = var1.getInetSocketAddress().getHostString();
         } catch (Exception var4) {
            var4.printStackTrace();
         }
      }
   }

   public boolean isConnect() {
      return this.connect;
   }

   public boolean isDisconnect() {
      return !this.connect;
   }
}
