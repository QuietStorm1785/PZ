#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/Channel.h"
#include "de/btobastian/javacord/entities/impl/ImplServer/3.h"
#include "de/btobastian/javacord/listener/channel/ChannelCreateListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplServer {
public:
   ImplServer$3$1(3 var1, Channel var2) {
      this.this$1 = var1;
      this.val$channel = var2;
   }

    void run() {
      List<ChannelCreateListener> listeners = ImplServer.access$100(this.this$1.this$0).getListeners(ChannelCreateListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onChannelCreate(ImplServer.access$100(this.this$1.this$0), this.val$channel);
            } catch (Throwable var7) {
               ImplServer.access$000().warn("Uncaught exception in ChannelCreateListener!", var7);
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
