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


class FactionChat : public ChatBase {
public:
    public FactionChat(ByteBuffer var1, ChatTab var2, IsoPlayer var3) {
      super(var1, ChatType.faction, var2, var3);
      if (!this.isCustomSettings()) {
         this.setSettings(getDefaultSettings());
      }
   }

    public FactionChat(int var1, ChatTab var2) {
      super(var1, ChatType.faction, var2);
      if (!this.isCustomSettings()) {
         this.setSettings(getDefaultSettings());
      }
   }

    static ChatSettings getDefaultSettings() {
    ChatSettings var0 = std::make_shared<ChatSettings>();
      var0.setBold(true);
      var0.setFontColor(Color.darkGreen);
      var0.setShowAuthor(true);
      var0.setShowChatTitle(true);
      var0.setShowTimestamp(true);
      var0.setUnique(false);
    return var0;
   }
}
} // namespace defaultChats
} // namespace chat
} // namespace zombie
