#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/impl/ImplServer.h"
#include "de/btobastian/javacord/listener/server/ServerChangeNameListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {


class GuildUpdateHandler {
public:
   GuildUpdateHandler$1(GuildUpdateHandler var1, ImplServer var2, std::string var3) {
      this.this$0 = var1;
      this.val$server = var2;
      this.val$oldName = var3;
   }

    void run() {
      List<ServerChangeNameListener> listeners = GuildUpdateHandler.access$000(this.this$0).getListeners(ServerChangeNameListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onServerChangeName(GuildUpdateHandler.access$100(this.this$0), this.val$server, this.val$oldName);
            } catch (Throwable var7) {
               GuildUpdateHandler.access$200().warn("Uncaught exception in ServerChangeNameListener!", var7);
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
