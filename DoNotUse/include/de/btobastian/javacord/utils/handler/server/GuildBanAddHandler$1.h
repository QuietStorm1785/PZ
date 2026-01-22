#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/listener/server/ServerMemberBanListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {


class GuildBanAddHandler {
public:
   GuildBanAddHandler$1(GuildBanAddHandler var1, User var2, Server var3) {
      this.this$0 = var1;
      this.val$user = var2;
      this.val$server = var3;
   }

    void run() {
      List<ServerMemberBanListener> listeners = GuildBanAddHandler.access$000(this.this$0).getListeners(ServerMemberBanListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onServerMemberBan(GuildBanAddHandler.access$100(this.this$0), this.val$user, this.val$server);
            } catch (Throwable var7) {
               GuildBanAddHandler.access$200().warn("Uncaught exception in ServerMemberBanListener!", var7);
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
