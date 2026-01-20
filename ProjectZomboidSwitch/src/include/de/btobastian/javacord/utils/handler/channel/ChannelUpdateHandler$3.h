#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/Channel.h"
#include "de/btobastian/javacord/listener/channel/ChannelChangePositionListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace channel {


class ChannelUpdateHandler {
public:
   ChannelUpdateHandler$3(ChannelUpdateHandler var1, Channel var2, int var3) {
      this.this$0 = var1;
      this.val$channel = var2;
      this.val$oldPosition = var3;
   }

    void run() {
      List<ChannelChangePositionListener> listeners = ChannelUpdateHandler.access$500(this.this$0).getListeners(ChannelChangePositionListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onChannelChangePosition(ChannelUpdateHandler.access$600(this.this$0), this.val$channel, this.val$oldPosition);
            } catch (Throwable var7) {
               ChannelUpdateHandler.access$200().warn("Uncaught exception in ChannelChangePositionListener!", var7);
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
