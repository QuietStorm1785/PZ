package zombie.network;

import de.btobastian.javacord.DiscordAPI;
import de.btobastian.javacord.entities.Channel;
import de.btobastian.javacord.entities.message.Message;
import de.btobastian.javacord.listener.message.MessageCreateListener;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import zombie.debug.DebugLog;
import zombie.debug.DebugType;

class DiscordBot$Listener implements MessageCreateListener {
   DiscordBot$Listener(DiscordBot var1) {
      this.this$0 = var1;
   }

   public void onMessageCreate(DiscordAPI var1, Message var2) {
      if (this.this$0.current != null) {
         if (!var1.getYourself().getId().equals(var2.getAuthor().getId())) {
            if (var2.getChannelReceiver().getId().equals(this.this$0.current.getId())) {
               DebugLog.log(DebugType.Network, "DISCORD: get message on current channel");
               DebugLog.log(DebugType.Network, "DISCORD: send message = \"" + var2.getContent() + "\" for " + var2.getAuthor().getName() + ")");
               String var3 = this.replaceChannelIDByItsName(var1, var2);
               var3 = this.removeSmilesAndImages(var3);
               if (!var3.isEmpty() && !var3.matches("^\\s$")) {
                  this.this$0.sender.sendMessageFromDiscord(var2.getAuthor().getName(), var3);
               }
            }
         }
      }
   }

   private String replaceChannelIDByItsName(DiscordAPI var1, Message var2) {
      String var3 = var2.getContent();
      Pattern var4 = Pattern.compile("<#(\\d+)>");
      Matcher var5 = var4.matcher(var2.getContent());
      if (var5.find()) {
         for (int var6 = 1; var6 <= var5.groupCount(); var6++) {
            Channel var7 = var1.getChannelById(var5.group(var6));
            if (var7 != null) {
               var3 = var3.replaceAll("<#" + var5.group(var6) + ">", "#" + var7.getName());
            }
         }
      }

      return var3;
   }

   private String removeSmilesAndImages(String var1) {
      StringBuilder var2 = new StringBuilder();
      char[] var3 = var1.toCharArray();
      int var4 = var3.length;

      for (int var5 = 0; var5 < var4; var5++) {
         Character var6 = var3[var5];
         if (!Character.isLowSurrogate(var6) && !Character.isHighSurrogate(var6)) {
            var2.append(var6);
         }
      }

      return var2.toString();
   }
}
