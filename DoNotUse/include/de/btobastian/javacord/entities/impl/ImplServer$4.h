#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/VoiceChannel.h"
#include "de/btobastian/javacord/entities/impl/ImplServer/4/1.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplServer {
public:
   ImplServer$4(ImplServer var1, std::string var2) {
      this.this$0 = var1;
      this.val$name = var2;
   }

    VoiceChannel call() {
    VoiceChannel channel = (VoiceChannel)ImplServer.access$300(this.this$0, this.val$name, true);
      ImplServer.access$000()
         .info("Created channel in server {} (name: {}, voice: {}, id: {})", new Object[]{this.this$0, channel.getName(), true, channel.getId()});
      ImplServer.access$100(this.this$0).getThreadPool().getSingleThreadExecutorService("listeners").submit(std::make_shared<1>(this, channel));
    return channel;
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
