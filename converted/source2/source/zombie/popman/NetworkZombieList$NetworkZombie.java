package zombie.popman;

import java.util.LinkedList;
import zombie.characters.IsoZombie;
import zombie.core.raknet.UdpConnection;

public class NetworkZombieList$NetworkZombie {
   final LinkedList<IsoZombie> zombies = new LinkedList<>();
   final UdpConnection connection;

   public NetworkZombieList$NetworkZombie(UdpConnection var1) {
      this.connection = var1;
   }
}
