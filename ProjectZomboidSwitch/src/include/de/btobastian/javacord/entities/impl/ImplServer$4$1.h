#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/VoiceChannel.h"
#include "de/btobastian/javacord/entities/impl/ImplServer/4.h"
#include "de/btobastian/javacord/listener/voicechannel/VoiceChannelCreateListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplServer {
public:
   ImplServer$4$1(4 var1, VoiceChannel var2) {
      this.this$1 = var1;
      this.val$channel = var2;
   }

    void run() {
      List<VoiceChannelCreateListener> listeners = ImplServer.access$100(this.this$1.this$0).getListeners(VoiceChannelCreateListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onVoiceChannelCreate(ImplServer.access$100(this.this$1.this$0), this.val$channel);
            } catch (Throwable var7) {
               ImplServer.access$000().warn("Uncaught exception in VoiceChannelCreateListener!", var7);
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
