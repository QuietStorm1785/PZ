#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/impl/ImplServer/12.h"
#include "de/btobastian/javacord/listener/server/ServerChangeNameListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplServer {
public:
   ImplServer$12$1(12 var1, std::string var2) {
      this.this$1 = var1;
      this.val$oldName = var2;
   }

    void run() {
      List<ServerChangeNameListener> listeners = ImplServer.access$100(this.this$1.this$0).getListeners(ServerChangeNameListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onServerChangeName(ImplServer.access$100(this.this$1.this$0), this.this$1.this$0, this.val$oldName);
            } catch (Throwable var7) {
               ImplServer.access$000().warn("Uncaught exception in ServerChangeNameListener!", var7);
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
