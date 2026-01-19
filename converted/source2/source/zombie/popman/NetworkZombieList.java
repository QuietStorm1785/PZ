package zombie.popman;

import java.util.LinkedList;
import zombie.core.raknet.UdpConnection;
import zombie.popman.NetworkZombieList.NetworkZombie;

public class NetworkZombieList {
   final LinkedList<NetworkZombie> networkZombies = new LinkedList<>();
   public Object lock = new Object();

   public NetworkZombie getNetworkZombie(UdpConnection var1) {
      if (var1 == null) {
         return null;
      } else {
         for (NetworkZombie var3 : this.networkZombies) {
            if (var3.connection == var1) {
               return var3;
            }
         }

         NetworkZombie var4 = new NetworkZombie(var1);
         this.networkZombies.add(var4);
         return var4;
      }
   }
}
