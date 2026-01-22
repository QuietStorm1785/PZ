#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/impl/ImplCustomEmoji/3.h"
#include "de/btobastian/javacord/listener/server/CustomEmojiDeleteListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplCustomEmoji {
public:
   ImplCustomEmoji$3$1(3 var1) {
      this.this$1 = var1;
   }

    void run() {
      List<CustomEmojiDeleteListener> listeners = ImplCustomEmoji.access$200(this.this$1.this$0).getListeners(CustomEmojiDeleteListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            listener.onCustomEmojiDelete(ImplCustomEmoji.access$200(this.this$1.this$0), this.this$1.this$0);
         }
      }
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
