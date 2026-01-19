package zombie.network;

import java.nio.ByteBuffer;
import zombie.core.raknet.UdpConnection;

public interface PacketTypes$CallbackServerProcess {
   void call(ByteBuffer var1, UdpConnection var2, short var3) throws Exception;
}
