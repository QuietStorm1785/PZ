#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/VoiceChannel.h"
#include "de/btobastian/javacord/listener/voicechannel/VoiceChannelChangeNameListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace channel {


class ChannelUpdateHandler {
public:
   ChannelUpdateHandler$6(ChannelUpdateHandler var1, VoiceChannel var2, std::string var3) {
      this.this$0 = var1;
      this.val$channel = var2;
      this.val$oldName = var3;
   }

    void run() {
      List<VoiceChannelChangeNameListener> listeners = ChannelUpdateHandler.access$1100(this.this$0).getListeners(VoiceChannelChangeNameListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onVoiceChannelChangeName(ChannelUpdateHandler.access$1200(this.this$0), this.val$channel, this.val$oldName);
            } catch (Throwable var7) {
               ChannelUpdateHandler.access$200().warn("Uncaught exception in VoiceChannelChangeNameListener!", var7);
            }
         }
      }
   }
}
} // namespace channel
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
