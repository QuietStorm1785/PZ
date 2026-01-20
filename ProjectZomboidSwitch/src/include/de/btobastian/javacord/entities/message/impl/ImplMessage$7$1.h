#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/message/impl/ImplMessage/7.h"
#include "de/btobastian/javacord/listener/message/MessageEditListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {
namespace impl {


class ImplMessage {
public:
   ImplMessage$7$1(7 var1, std::string var2) {
      this.this$1 = var1;
      this.val$oldContent = var2;
   }

    void run() {
      List<MessageEditListener> listeners = ImplMessage.access$100(this.this$1.this$0).getListeners(MessageEditListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onMessageEdit(ImplMessage.access$100(this.this$1.this$0), this.this$1.this$0, this.val$oldContent);
            } catch (Throwable var7) {
               ImplMessage.access$000().warn("Uncaught exception in MessageEditListener!", var7);
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
