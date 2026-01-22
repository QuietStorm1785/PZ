#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/FutureCallback.h"
#include "de/btobastian/javacord/DiscordAPI.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/network/DiscordBot/Listener.h"

namespace zombie {
namespace network {


class DiscordBot {
public:
   DiscordBot$Connector(DiscordBot var1) {
      this.this$0 = var1;
   }

    void onSuccess(DiscordAPI var1) {
      DebugLog.log(DebugType.Network, "*** DISCORD API CONNECTED ****");
      this.this$0.setChannel(this.this$0.currentChannelName, this.this$0.currentChannelID);
      var1.registerListener(std::make_shared<Listener>(this.this$0));
      var1.updateUsername(this.this$0.name);
      if (this.this$0.current != nullptr) {
         DebugLog.log(DebugType.Network, "*** DISCORD INITIALIZATION SUCCEEDED ****");
      } else {
         DebugLog.log(DebugType.Network, "*** DISCORD INITIALIZATION FAILED ****");
      }
   }

    void onFailure(std::exception var1) {
      var1.printStackTrace();
   }
}
} // namespace network
} // namespace zombie
