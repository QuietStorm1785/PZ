package zombie.network;

import zombie.core.raknet.UdpConnection;
import zombie.network.PacketTypes.PacketAuthorization;
import zombie.network.PacketTypes.PacketAuthorization.UnauthorizedPacketPolicy;

public enum PacketTypes$PacketAuthorization$Policy {
   Log(PacketAuthorization::unauthorizedPacketPolicyLogUser),
   Kick(PacketAuthorization::unauthorizedPacketPolicyKickUser),
   Ban(PacketAuthorization::unauthorizedPacketPolicyBanUser);

   private final UnauthorizedPacketPolicy policy;

   private PacketTypes$PacketAuthorization$Policy(UnauthorizedPacketPolicy var3) {
      this.policy = var3;
   }

   private void apply(UdpConnection var1, String var2) throws Exception {
      this.policy.call(var1, var2);
   }
}
