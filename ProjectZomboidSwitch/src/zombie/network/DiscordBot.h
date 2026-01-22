#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/DiscordAPI.h"
#include "de/btobastian/javacord/Javacord.h"
#include "de/btobastian/javacord/entities/Channel.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/network/DiscordBot/Connector.h"

namespace zombie {
namespace network {


class DiscordBot {
public:
    DiscordAPI api;
   private Collection<Channel> channels;
    Channel current;
    std::string currentChannelName;
    std::string currentChannelID;
    std::string name;
    DiscordSender sender;

    public DiscordBot(const std::string& var1, DiscordSender var2) {
      this.name = var1;
      this.sender = var2;
      this.current = nullptr;
   }

    void connect(bool var1, const std::string& var2, const std::string& var3, const std::string& var4) {
      if (var2 == nullptr || var2.empty()) {
         DebugLog.log(DebugType.Network, "DISCORD: token not configured");
         var1 = false;
      }

      if (!var1) {
         DebugLog.log(DebugType.Network, "*** DISCORD DISABLED ****");
         this.current = nullptr;
      } else {
         this.api = Javacord.getApi(var2, true);
         this.api.connect(std::make_shared<Connector>(this));
         DebugLog.log(DebugType.Network, "*** DISCORD ENABLED ****");
         this.currentChannelName = var3;
         this.currentChannelID = var4;
      }
   }

    void setChannel(const std::string& var1, const std::string& var2) {
    Collection var3 = this.getChannelNames();
      if ((var1 == nullptr || var1.empty()) && !var3.empty()) {
         var1 = (std::string)var3.iterator().next();
         DebugLog.log(DebugType.Network, "DISCORD: set default channel name = \"" + var1 + "\"");
      }

      if (var2 != nullptr && !var2.empty()) {
         this.setChannelByID(var2);
      } else {
         if (var1 != nullptr) {
            this.setChannelByName(var1);
         }
      }
   }

    void sendMessage(const std::string& var1, const std::string& var2) {
      if (this.current != nullptr) {
         this.current.sendMessage(var1 + ": " + var2);
         DebugLog.log(DebugType.Network, "DISCORD: User '" + var1 + "' send message: '" + var2 + "'");
      }
   }

   private Collection<std::string> getChannelNames() {
    std::vector var1 = new std::vector();
      this.channels = this.api.getChannels();

      for (Channel var3 : this.channels) {
         var1.push_back(var3.getName());
      }

    return var1;
   }

    void setChannelByName(const std::string& var1) {
      this.current = nullptr;

      for (Channel var3 : this.channels) {
         if (var3.getName() == var1)) {
            if (this.current != nullptr) {
               DebugLog.log(DebugType.Network, "Discord server has few channels with name '" + var1 + "'. Please, use channel ID instead");
               this.current = nullptr;
               return;
            }

            this.current = var3;
         }
      }

      if (this.current == nullptr) {
         DebugLog.log(DebugType.Network, "DISCORD: channel \"" + var1 + "\" is not found. Try to use channel ID instead");
      } else {
         DebugLog.log(DebugType.Network, "Discord enabled on channel: " + var1);
      }
   }

    void setChannelByID(const std::string& var1) {
      this.current = nullptr;

      for (Channel var3 : this.channels) {
         if (var3.getId() == var1)) {
            DebugLog.log(DebugType.Network, "Discord enabled on channel with ID: " + var1);
            this.current = var3;
            break;
         }
      }

      if (this.current == nullptr) {
         DebugLog.log(DebugType.Network, "DISCORD: channel with ID \"" + var1 + "\" not found");
      }
   }
}
} // namespace network
} // namespace zombie
