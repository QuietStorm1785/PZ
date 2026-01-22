#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/message/Message.h"
#include "de/btobastian/javacord/listener/message/ReactionRemoveAllListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace message {


class MessageReactionRemoveAllHandler {
public:
   MessageReactionRemoveAllHandler$1(MessageReactionRemoveAllHandler var1, Message var2, List var3) {
      this.this$0 = var1;
      this.val$message = var2;
      this.val$reactions = var3;
   }

    void run() {
      List<ReactionRemoveAllListener> listeners = MessageReactionRemoveAllHandler.access$000(this.this$0).getListeners(ReactionRemoveAllListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onReactionRemoveAll(MessageReactionRemoveAllHandler.access$100(this.this$0), this.val$message, this.val$reactions);
            } catch (Throwable var7) {
               MessageReactionRemoveAllHandler.access$200().warn("Uncaught exception in ReactionRemoveAllListener!", var7);
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
