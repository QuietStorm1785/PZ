#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/impl/ImplServer.h"
#include "de/btobastian/javacord/listener/server/ServerChangeOwnerListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {


class GuildUpdateHandler {
public:
   GuildUpdateHandler$3(GuildUpdateHandler var1, ImplServer var2, std::string var3) {
      this.this$0 = var1;
      this.val$server = var2;
      this.val$oldOwnerId = var3;
   }

    void run() {
      List<ServerChangeOwnerListener> listeners = GuildUpdateHandler.access$500(this.this$0).getListeners(ServerChangeOwnerListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onServerChangeOwner(GuildUpdateHandler.access$600(this.this$0), this.val$server, this.val$oldOwnerId);
            } catch (Throwable var7) {
               GuildUpdateHandler.access$200().warn("Uncaught exception in ServerChangeOwnerListener!", var7);
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
