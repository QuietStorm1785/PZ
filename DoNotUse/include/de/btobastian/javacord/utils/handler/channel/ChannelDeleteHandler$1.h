#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/Channel.h"
#include "de/btobastian/javacord/listener/channel/ChannelDeleteListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace channel {


class ChannelDeleteHandler {
public:
   ChannelDeleteHandler$1(ChannelDeleteHandler var1, Channel var2) {
      this.this$0 = var1;
      this.val$channel = var2;
   }

    void run() {
      List<ChannelDeleteListener> listeners = ChannelDeleteHandler.access$000(this.this$0).getListeners(ChannelDeleteListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onChannelDelete(ChannelDeleteHandler.access$100(this.this$0), this.val$channel);
            } catch (Throwable var7) {
               ChannelDeleteHandler.access$200().warn("Uncaught exception in ChannelDeleteListener!", var7);
            }
         }
      }
   }
}
} // namespace channel
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
