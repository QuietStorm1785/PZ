#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/message/Message.h"
#include "de/btobastian/javacord/listener/message/MessageEditListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace message {


class MessageUpdateHandler {
public:
   MessageUpdateHandler$1(MessageUpdateHandler var1, Message var2, std::string var3) {
      this.this$0 = var1;
      this.val$message = var2;
      this.val$oldContent = var3;
   }

    void run() {
      List<MessageEditListener> listeners = MessageUpdateHandler.access$000(this.this$0).getListeners(MessageEditListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onMessageEdit(MessageUpdateHandler.access$100(this.this$0), this.val$message, this.val$oldContent);
            } catch (Throwable var7) {
               MessageUpdateHandler.access$200().warn("Uncaught exception in MessageEditListener!", var7);
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
