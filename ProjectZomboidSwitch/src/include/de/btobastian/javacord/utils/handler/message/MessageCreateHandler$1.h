#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/message/Message.h"
#include "de/btobastian/javacord/listener/message/MessageCreateListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace message {


class MessageCreateHandler {
public:
   MessageCreateHandler$1(MessageCreateHandler var1, Message var2) {
      this.this$0 = var1;
      this.val$message = var2;
   }

    void run() {
      List<MessageCreateListener> listeners = MessageCreateHandler.access$000(this.this$0).getListeners(MessageCreateListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onMessageCreate(MessageCreateHandler.access$100(this.this$0), this.val$message);
            } catch (Throwable var7) {
               MessageCreateHandler.access$200().warn("Uncaught exception in MessageCreateListener!", var7);
            }
         }
      }
   }
}
} // namespace message
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
