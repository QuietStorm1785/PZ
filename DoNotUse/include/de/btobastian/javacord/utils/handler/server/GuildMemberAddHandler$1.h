#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/listener/server/ServerMemberAddListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {


class GuildMemberAddHandler {
public:
   GuildMemberAddHandler$1(GuildMemberAddHandler var1, User var2, Server var3) {
      this.this$0 = var1;
      this.val$user = var2;
      this.val$server = var3;
   }

    void run() {
      List<ServerMemberAddListener> listeners = GuildMemberAddHandler.access$000(this.this$0).getListeners(ServerMemberAddListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onServerMemberAdd(GuildMemberAddHandler.access$100(this.this$0), this.val$user, this.val$server);
            } catch (Throwable var7) {
               GuildMemberAddHandler.access$200().warn("Uncaught exception in ServerMemberAddListener!", var7);
            }
         }
      }
   }
}
} // namespace server
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
