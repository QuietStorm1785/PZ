#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/Channel.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/listener/message/TypingStartListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace message {


class TypingStartHandler {
public:
   TypingStartHandler$1(TypingStartHandler var1, User var2, Channel var3) {
      this.this$0 = var1;
      this.val$user = var2;
      this.val$channel = var3;
   }

    void run() {
      List<TypingStartListener> listeners = TypingStartHandler.access$000(this.this$0).getListeners(TypingStartListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onTypingStart(TypingStartHandler.access$100(this.this$0), this.val$user, this.val$channel);
            } catch (Throwable var7) {
               TypingStartHandler.access$200().warn("Uncaught exception in TypingStartListener!", var7);
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
