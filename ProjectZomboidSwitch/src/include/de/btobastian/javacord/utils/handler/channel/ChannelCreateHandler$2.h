#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/VoiceChannel.h"
#include "de/btobastian/javacord/listener/voicechannel/VoiceChannelCreateListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace channel {


class ChannelCreateHandler {
public:
   ChannelCreateHandler$2(ChannelCreateHandler var1, VoiceChannel var2) {
      this.this$0 = var1;
      this.val$channel = var2;
   }

    void run() {
      List<VoiceChannelCreateListener> listeners = ChannelCreateHandler.access$300(this.this$0).getListeners(VoiceChannelCreateListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onVoiceChannelCreate(ChannelCreateHandler.access$400(this.this$0), this.val$channel);
            } catch (Throwable var7) {
               ChannelCreateHandler.access$200().warn("Uncaught exception in VoiceChannelCreateListener!", var7);
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
