#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/listener/voice/UserLeaveVoiceChannelListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace voice {


class VoiceStateUpdateHandler {
public:
   VoiceStateUpdateHandler$2(VoiceStateUpdateHandler var1, User var2) {
      this.this$0 = var1;
      this.val$userPassed = var2;
   }

    void run() {
      List<UserLeaveVoiceChannelListener> listeners = VoiceStateUpdateHandler.access$300(this.this$0).getListeners(UserLeaveVoiceChannelListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onUserLeaveVoiceChannel(VoiceStateUpdateHandler.access$400(this.this$0), this.val$userPassed);
            } catch (Throwable var7) {
               VoiceStateUpdateHandler.access$200().warn("Uncaught exception in UserLeaveVoiceChannelListener!", var7);
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
