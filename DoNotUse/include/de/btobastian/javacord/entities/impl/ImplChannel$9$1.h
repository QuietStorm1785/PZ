#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/impl/ImplChannel/9.h"
#include "de/btobastian/javacord/listener/channel/ChannelChangeNameListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplChannel {
public:
   ImplChannel$9$1(9 var1, std::string var2) {
      this.this$1 = var1;
      this.val$oldName = var2;
   }

    void run() {
      List<ChannelChangeNameListener> listeners = ImplChannel.access$100(this.this$1.this$0).getListeners(ChannelChangeNameListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onChannelChangeName(ImplChannel.access$100(this.this$1.this$0), this.this$1.this$0, this.val$oldName);
            } catch (Throwable var7) {
               ImplChannel.access$000().warn("Uncaught exception in ChannelChangeNameListener!", var7);
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
