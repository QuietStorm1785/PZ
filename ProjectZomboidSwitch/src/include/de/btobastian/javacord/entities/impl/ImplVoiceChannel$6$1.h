#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/impl/ImplVoiceChannel/6.h"
#include "de/btobastian/javacord/listener/voicechannel/VoiceChannelChangeNameListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplVoiceChannel {
public:
   ImplVoiceChannel$6$1(6 var1, std::string var2) {
      this.this$1 = var1;
      this.val$oldName = var2;
   }

    void run() {
      List<VoiceChannelChangeNameListener> listeners = ImplVoiceChannel.access$100(this.this$1.this$0).getListeners(VoiceChannelChangeNameListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onVoiceChannelChangeName(ImplVoiceChannel.access$100(this.this$1.this$0), this.this$1.this$0, this.val$oldName);
            } catch (Throwable var7) {
               ImplVoiceChannel.access$000().warn("Uncaught exception in VoiceChannelChangeNameListener!", var7);
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
