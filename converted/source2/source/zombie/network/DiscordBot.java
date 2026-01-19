package zombie.network;

import de.btobastian.javacord.DiscordAPI;
import de.btobastian.javacord.Javacord;
import de.btobastian.javacord.entities.Channel;
import java.util.ArrayList;
import java.util.Collection;
import zombie.debug.DebugLog;
import zombie.debug.DebugType;
import zombie.network.DiscordBot.Connector;

public class DiscordBot {
   private DiscordAPI api;
   private Collection<Channel> channels;
   private Channel current;
   private String currentChannelName;
   private String currentChannelID;
   private String name;
   private DiscordSender sender;

   public DiscordBot(String var1, DiscordSender var2) {
      this.name = var1;
      this.sender = var2;
      this.current = null;
   }

   public void connect(boolean var1, String var2, String var3, String var4) {
      if (var2 == null || var2.isEmpty()) {
         DebugLog.log(DebugType.Network, "DISCORD: token not configured");
         var1 = false;
      }

      if (!var1) {
         DebugLog.log(DebugType.Network, "*** DISCORD DISABLED ****");
         this.current = null;
      } else {
         this.api = Javacord.getApi(var2, true);
         this.api.connect(new Connector(this));
         DebugLog.log(DebugType.Network, "*** DISCORD ENABLED ****");
         this.currentChannelName = var3;
         this.currentChannelID = var4;
      }
   }

   private void setChannel(String var1, String var2) {
      Collection var3 = this.getChannelNames();
      if ((var1 == null || var1.isEmpty()) && !var3.isEmpty()) {
         var1 = (String)var3.iterator().next();
         DebugLog.log(DebugType.Network, "DISCORD: set default channel name = \"" + var1 + "\"");
      }

      if (var2 != null && !var2.isEmpty()) {
         this.setChannelByID(var2);
      } else {
         if (var1 != null) {
            this.setChannelByName(var1);
         }
      }
   }

   public void sendMessage(String var1, String var2) {
      if (this.current != null) {
         this.current.sendMessage(var1 + ": " + var2);
         DebugLog.log(DebugType.Network, "DISCORD: User '" + var1 + "' send message: '" + var2 + "'");
      }
   }

   private Collection<String> getChannelNames() {
      ArrayList var1 = new ArrayList();
      this.channels = this.api.getChannels();

      for (Channel var3 : this.channels) {
         var1.add(var3.getName());
      }

      return var1;
   }

   private void setChannelByName(String var1) {
      this.current = null;

      for (Channel var3 : this.channels) {
         if (var3.getName().equals(var1)) {
            if (this.current != null) {
               DebugLog.log(DebugType.Network, "Discord server has few channels with name '" + var1 + "'. Please, use channel ID instead");
               this.current = null;
               return;
            }

            this.current = var3;
         }
      }

      if (this.current == null) {
         DebugLog.log(DebugType.Network, "DISCORD: channel \"" + var1 + "\" is not found. Try to use channel ID instead");
      } else {
         DebugLog.log(DebugType.Network, "Discord enabled on channel: " + var1);
      }
   }

   private void setChannelByID(String var1) {
      this.current = null;

      for (Channel var3 : this.channels) {
         if (var3.getId().equals(var1)) {
            DebugLog.log(DebugType.Network, "Discord enabled on channel with ID: " + var1);
            this.current = var3;
            break;
         }
      }

      if (this.current == null) {
         DebugLog.log(DebugType.Network, "DISCORD: channel with ID \"" + var1 + "\" not found");
      }
   }
}
