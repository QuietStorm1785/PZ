#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/impl/ImplServer/10.h"
#include "de/btobastian/javacord/listener/server/ServerMemberRemoveListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplServer {
public:
   ImplServer$10$1(10 var1, User var2) {
      this.this$1 = var1;
      this.val$user = var2;
   }

    void run() {
      List<ServerMemberRemoveListener> listeners = ImplServer.access$100(this.this$1.this$0).getListeners(ServerMemberRemoveListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onServerMemberRemove(ImplServer.access$100(this.this$1.this$0), this.val$user, this.this$1.this$0);
            } catch (Throwable var7) {
               ImplServer.access$000().warn("Uncaught exception in ServerMemberRemoveListener!", var7);
            }
         }
      }
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
