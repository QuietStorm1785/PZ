#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/Channel.h"
#include "de/btobastian/javacord/listener/channel/ChannelChangeNameListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace channel {


class ChannelUpdateHandler {
public:
   ChannelUpdateHandler$1(ChannelUpdateHandler var1, Channel var2, std::string var3) {
      this.this$0 = var1;
      this.val$channel = var2;
      this.val$oldName = var3;
   }

    void run() {
      List<ChannelChangeNameListener> listeners = ChannelUpdateHandler.access$000(this.this$0).getListeners(ChannelChangeNameListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onChannelChangeName(ChannelUpdateHandler.access$100(this.this$0), this.val$channel, this.val$oldName);
            } catch (Throwable var7) {
               ChannelUpdateHandler.access$200().warn("Uncaught exception in ChannelChangeNameListener!", var7);
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
