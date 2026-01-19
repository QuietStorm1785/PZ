package zombie.debug.options;

import zombie.debug.options.Network.Client;
import zombie.debug.options.Network.PublicServerUtil;
import zombie.debug.options.Network.Server;

public final class Network extends OptionGroup {
   public final Client Client = new Client(this, this.Group);
   public final Server Server = new Server(this, this.Group);
   public final PublicServerUtil PublicServerUtil = new PublicServerUtil(this, this.Group);

   public Network() {
      super("Network");
   }
}
