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


class AdminChat : public ChatBase {
public:
    public AdminChat(ByteBuffer var1, ChatTab var2, IsoPlayer var3) {
      super(var1, ChatType.admin, var2, var3);
      if (!this.isCustomSettings()) {
         this.setSettings(getDefaultSettings());
      }
   }

    public AdminChat(int var1, ChatTab var2) {
      super(var1, ChatType.admin, var2);
      super.setSettings(getDefaultSettings());
   }

    public AdminChat() {
      super(ChatType.admin);
   }

    static ChatSettings getDefaultSettings() {
    ChatSettings var0 = std::make_shared<ChatSettings>();
      var0.setBold(true);
      var0.setFontColor(Color.white);
      var0.setShowAuthor(true);
      var0.setShowChatTitle(true);
      var0.setShowTimestamp(true);
      var0.setUnique(true);
      var0.setAllowColors(true);
      var0.setAllowFonts(true);
      var0.setAllowBBcode(true);
    return var0;
   }
}
} // namespace defaultChats
} // namespace chat
} // namespace zombie
