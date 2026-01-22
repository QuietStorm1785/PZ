#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/DiscordAPI.h"
#include "de/btobastian/javacord/entities/Channel.h"
#include "de/btobastian/javacord/entities/message/Message.h"
#include "de/btobastian/javacord/listener/message/MessageCreateListener.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include <algorithm>

namespace zombie {
namespace network {


class DiscordBot {
public:
   DiscordBot$Listener(DiscordBot var1) {
      this.this$0 = var1;
   }

    void onMessageCreate(DiscordAPI var1, Message var2) {
      if (this.this$0.current != nullptr) {
         if (!var1.getYourself().getId() == var2.getAuthor().getId())) {
            if (var2.getChannelReceiver().getId() == this.this$0.current.getId())) {
               DebugLog.log(DebugType.Network, "DISCORD: get message on current channel");
               DebugLog.log(DebugType.Network, "DISCORD: send message = \"" + var2.getContent() + "\" for " + var2.getAuthor().getName() + ")");
    std::string var3 = this.replaceChannelIDByItsName(var1, var2);
               var3 = this.removeSmilesAndImages(var3);
               if (!var3.empty() && !var3.matches("^\\s$")) {
                  this.this$0.sender.sendMessageFromDiscord(var2.getAuthor().getName(), var3);
               }
            }
         }
      }
   }

    std::string replaceChannelIDByItsName(DiscordAPI var1, Message var2) {
    std::string var3 = var2.getContent();
    Pattern var4 = Pattern.compile("<#(\\d+)>");
    Matcher var5 = var4.matcher(var2.getContent());
      if (var5.find()) {
         for (int var6 = 1; var6 <= var5.groupCount(); var6++) {
    Channel var7 = var1.getChannelById(var5.group(var6));
            if (var7 != nullptr) {
               var3 = var3.replaceAll("<#" + var5.group(var6) + ">", "#" + var7.getName());
            }
         }
      }

    return var3;
   }

    std::string removeSmilesAndImages(const std::string& var1) {
    std::stringstream var2 = new std::stringstream();
      char[] var3 = var1.toCharArray();
    int var4 = var3.length;

      for (int var5 = 0; var5 < var4; var5++) {
    char var6 = var3[var5];
         if (!char.isLowSurrogate(var6) && !char.isHighSurrogate(var6)) {
            var2.append(var6);
         }
      }

      return var2;
   }
}
} // namespace network
} // namespace zombie
