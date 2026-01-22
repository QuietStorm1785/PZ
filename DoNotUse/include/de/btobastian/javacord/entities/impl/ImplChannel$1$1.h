#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/impl/ImplChannel/1.h"
#include "de/btobastian/javacord/listener/channel/ChannelDeleteListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplChannel {
public:
   ImplChannel$1$1(1 var1) {
      this.this$1 = var1;
   }

    void run() {
      List<ChannelDeleteListener> listeners = ImplChannel.access$100(this.this$1.this$0).getListeners(ChannelDeleteListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            listener.onChannelDelete(ImplChannel.access$100(this.this$1.this$0), this.this$1.this$0);
         }
      }
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
