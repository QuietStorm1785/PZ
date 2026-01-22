#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/chat/ChatBase.h"
#include "zombie/chat/ChatSettings.h"
#include "zombie/chat/ChatTab.h"
#include "zombie/core/Color.h"
#include "zombie/network/chat/ChatType.h"
#include <filesystem>

namespace zombie {
namespace chat {
namespace defaultChats {


class SafehouseChat : public ChatBase {
public:
    public SafehouseChat(ByteBuffer var1, ChatTab var2, IsoPlayer var3) {
      super(var1, ChatType.safehouse, var2, var3);
      if (!this.isCustomSettings()) {
         this.setSettings(getDefaultSettings());
      }
   }

    public SafehouseChat(int var1, ChatTab var2) {
      super(var1, ChatType.safehouse, var2);
      if (!this.isCustomSettings()) {
         this.setSettings(getDefaultSettings());
      }
   }

    static ChatSettings getDefaultSettings() {
    ChatSettings var0 = std::make_shared<ChatSettings>();
      var0.setBold(true);
      var0.setFontColor(Color.lightGreen);
      var0.setShowAuthor(true);
      var0.setShowChatTitle(true);
      var0.setShowTimestamp(true);
      var0.setUnique(true);
    return var0;
   }
}
} // namespace defaultChats
} // namespace chat
} // namespace zombie
