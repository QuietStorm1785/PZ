#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/impl/ImplVoiceChannel.h"
#include "de/btobastian/javacord/listener/voice/UserJoinVoiceChannelListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace voice {


class VoiceStateUpdateHandler {
public:
   VoiceStateUpdateHandler$1(VoiceStateUpdateHandler var1, User var2, ImplVoiceChannel var3) {
      this.this$0 = var1;
      this.val$userPassed = var2;
      this.val$channel = var3;
   }

    void run() {
      List<UserJoinVoiceChannelListener> listeners = VoiceStateUpdateHandler.access$000(this.this$0).getListeners(UserJoinVoiceChannelListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onUserJoinVoiceChannel(VoiceStateUpdateHandler.access$100(this.this$0), this.val$userPassed, this.val$channel);
            } catch (Throwable var7) {
               VoiceStateUpdateHandler.access$200().warn("Uncaught exception in UserJoinVoiceChannelListener!", var7);
            }
         }
      }
   }
}
} // namespace voice
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
