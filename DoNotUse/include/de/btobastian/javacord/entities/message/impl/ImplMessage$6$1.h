#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/message/impl/ImplMessage/6.h"
#include "de/btobastian/javacord/listener/message/MessageDeleteListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {
namespace impl {


class ImplMessage {
public:
   ImplMessage$6$1(6 var1) {
      this.this$1 = var1;
   }

    void run() {
      List<MessageDeleteListener> listeners = ImplMessage.access$100(this.this$1.this$0).getListeners(MessageDeleteListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onMessageDelete(ImplMessage.access$100(this.this$1.this$0), this.this$1.val$message);
            } catch (Throwable var7) {
               ImplMessage.access$000().warn("Uncaught exception in MessageDeleteListener!", var7);
            }
         }
      }
   }
}
} // namespace impl
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
