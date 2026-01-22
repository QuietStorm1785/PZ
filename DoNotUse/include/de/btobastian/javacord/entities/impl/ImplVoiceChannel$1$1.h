#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/impl/ImplVoiceChannel/1.h"
#include "de/btobastian/javacord/listener/voicechannel/VoiceChannelDeleteListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplVoiceChannel {
public:
   ImplVoiceChannel$1$1(1 var1) {
      this.this$1 = var1;
   }

    void run() {
      List<VoiceChannelDeleteListener> listeners = ImplVoiceChannel.access$100(this.this$1.this$0).getListeners(VoiceChannelDeleteListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onVoiceChannelDelete(ImplVoiceChannel.access$100(this.this$1.this$0), this.this$1.this$0);
            } catch (Throwable var7) {
               ImplVoiceChannel.access$000().warn("Uncaught exception in VoiceChannelDeleteListener!", var7);
            }
         }
      }
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
