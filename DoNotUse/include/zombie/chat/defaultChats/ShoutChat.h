#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/chat/ChatSettings.h"
#include "zombie/chat/ChatTab.h"
#include "zombie/core/Color.h"
#include "zombie/network/chat/ChatType.h"
#include <filesystem>

namespace zombie {
namespace chat {
namespace defaultChats {


class ShoutChat : public RangeBasedChat {
public:
    public ShoutChat(ByteBuffer var1, ChatTab var2, IsoPlayer var3) {
      super(var1, ChatType.shout, var2, var3);
      if (!this.isCustomSettings()) {
         this.setSettings(getDefaultSettings());
      }
   }

    public ShoutChat(int var1, ChatTab var2) {
      super(var1, ChatType.shout, var2);
      if (!this.isCustomSettings()) {
         this.setSettings(getDefaultSettings());
      }
   }

    public ShoutChat() {
      super(ChatType.shout);
      this.setSettings(getDefaultSettings());
   }

    static ChatSettings getDefaultSettings() {
    ChatSettings var0 = std::make_shared<ChatSettings>();
      var0.setBold(true);
      var0.setFontColor(std::make_shared<Color>(255, 51, 51, 255));
      var0.setShowAuthor(true);
      var0.setShowChatTitle(true);
      var0.setShowTimestamp(true);
      var0.setUnique(true);
      var0.setAllowColors(false);
      var0.setAllowFonts(false);
      var0.setAllowBBcode(false);
      var0.setEqualizeLineHeights(true);
      var0.setRange(60.0F);
    return var0;
   }
}
} // namespace defaultChats
} // namespace chat
} // namespace zombie
