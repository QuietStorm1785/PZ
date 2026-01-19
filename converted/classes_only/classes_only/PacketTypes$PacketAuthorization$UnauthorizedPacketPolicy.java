package zombie.network;

import zombie.core.raknet.UdpConnection;

public interface PacketTypes$PacketAuthorization$UnauthorizedPacketPolicy {
   void call(UdpConnection var1, String var2) throws Exception;
}
