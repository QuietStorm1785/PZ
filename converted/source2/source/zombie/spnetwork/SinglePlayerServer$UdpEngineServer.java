package zombie.spnetwork;

import java.nio.ByteBuffer;
import java.util.ArrayList;

public final class SinglePlayerServer$UdpEngineServer extends UdpEngine {
   public final ArrayList<UdpConnection> connections = new ArrayList<>();

   SinglePlayerServer$UdpEngineServer() {
      this.connections.add(new UdpConnection(this));
   }

   public void Send(ByteBuffer var1) {
      SinglePlayerClient.udpEngine.Receive(var1);
   }

   public void Receive(ByteBuffer var1) {
      int var2 = var1.get() & 255;
      short var3 = var1.getShort();
      SinglePlayerServer.addIncoming(var3, var1, SinglePlayerServer.udpEngine.connections.get(0));
   }
}
