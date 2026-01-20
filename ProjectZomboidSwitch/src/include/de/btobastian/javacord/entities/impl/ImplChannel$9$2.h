#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/impl/ImplChannel/9.h"
#include "de/btobastian/javacord/listener/channel/ChannelChangeTopicListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplChannel {
public:
   ImplChannel$9$2(9 var1, std::string var2) {
      this.this$1 = var1;
      this.val$oldTopic = var2;
   }

    void run() {
      List<ChannelChangeTopicListener> listeners = ImplChannel.access$100(this.this$1.this$0).getListeners(ChannelChangeTopicListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onChannelChangeTopic(ImplChannel.access$100(this.this$1.this$0), this.this$1.this$0, this.val$oldTopic);
            } catch (Throwable var7) {
               ImplChannel.access$000().warn("Uncaught exception in ChannelChangeTopicListener!", var7);
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
