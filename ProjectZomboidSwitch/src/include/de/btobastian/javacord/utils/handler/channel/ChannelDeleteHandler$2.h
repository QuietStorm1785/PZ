#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/VoiceChannel.h"
#include "de/btobastian/javacord/listener/voicechannel/VoiceChannelDeleteListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace channel {


class ChannelDeleteHandler {
public:
   ChannelDeleteHandler$2(ChannelDeleteHandler var1, VoiceChannel var2) {
      this.this$0 = var1;
      this.val$channel = var2;
   }

    void run() {
      List<VoiceChannelDeleteListener> listeners = ChannelDeleteHandler.access$300(this.this$0).getListeners(VoiceChannelDeleteListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onVoiceChannelDelete(ChannelDeleteHandler.access$400(this.this$0), this.val$channel);
            } catch (Throwable var7) {
               ChannelDeleteHandler.access$200().warn("Uncaught exception in VoiceChannelDeleteListener!", var7);
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
