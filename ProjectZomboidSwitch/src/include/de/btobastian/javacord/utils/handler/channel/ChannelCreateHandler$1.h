#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/Channel.h"
#include "de/btobastian/javacord/listener/channel/ChannelCreateListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace channel {


class ChannelCreateHandler {
public:
   ChannelCreateHandler$1(ChannelCreateHandler var1, Channel var2) {
      this.this$0 = var1;
      this.val$channel = var2;
   }

    void run() {
      List<ChannelCreateListener> listeners = ChannelCreateHandler.access$000(this.this$0).getListeners(ChannelCreateListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onChannelCreate(ChannelCreateHandler.access$100(this.this$0), this.val$channel);
            } catch (Throwable var7) {
               ChannelCreateHandler.access$200().warn("Uncaught exception in ChannelCreateListener!", var7);
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
