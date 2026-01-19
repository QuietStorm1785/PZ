package zombie.spnetwork;

import java.nio.ByteBuffer;

final class SinglePlayerClient$UdpEngineClient extends UdpEngine {
   private SinglePlayerClient$UdpEngineClient() {
   }

   public void Send(ByteBuffer var1) {
      SinglePlayerServer.udpEngine.Receive(var1);
   }

   public void Receive(ByteBuffer var1) {
      int var2 = var1.get() & 255;
      short var3 = var1.getShort();
      SinglePlayerClient.addIncoming(var3, var1);
   }
}
