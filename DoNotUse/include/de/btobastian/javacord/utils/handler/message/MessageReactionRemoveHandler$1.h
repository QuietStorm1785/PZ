#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/message/Reaction.h"
#include "de/btobastian/javacord/listener/message/ReactionRemoveListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace message {


class MessageReactionRemoveHandler {
public:
   MessageReactionRemoveHandler$1(MessageReactionRemoveHandler var1, Reaction var2, User var3) {
      this.this$0 = var1;
      this.val$reactionFinal = var2;
      this.val$user = var3;
   }

    void run() {
      List<ReactionRemoveListener> listeners = MessageReactionRemoveHandler.access$000(this.this$0).getListeners(ReactionRemoveListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onReactionRemove(MessageReactionRemoveHandler.access$100(this.this$0), this.val$reactionFinal, this.val$user);
            } catch (Throwable var7) {
               MessageReactionRemoveHandler.access$200().warn("Uncaught exception in ReactionRemoveListener!", var7);
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
