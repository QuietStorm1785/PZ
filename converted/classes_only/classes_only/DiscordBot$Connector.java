package zombie.network;

import com.google.common.util.concurrent.FutureCallback;
import de.btobastian.javacord.DiscordAPI;
import zombie.debug.DebugLog;
import zombie.debug.DebugType;
import zombie.network.DiscordBot.Listener;

class DiscordBot$Connector implements FutureCallback<DiscordAPI> {
   DiscordBot$Connector(DiscordBot var1) {
      this.this$0 = var1;
   }

   public void onSuccess(DiscordAPI var1) {
      DebugLog.log(DebugType.Network, "*** DISCORD API CONNECTED ****");
      this.this$0.setChannel(this.this$0.currentChannelName, this.this$0.currentChannelID);
      var1.registerListener(new Listener(this.this$0));
      var1.updateUsername(this.this$0.name);
      if (this.this$0.current != null) {
         DebugLog.log(DebugType.Network, "*** DISCORD INITIALIZATION SUCCEEDED ****");
      } else {
         DebugLog.log(DebugType.Network, "*** DISCORD INITIALIZATION FAILED ****");
      }
   }

   public void onFailure(Throwable var1) {
      var1.printStackTrace();
   }
}
