#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/chat/ChatMessage.h"
#include "zombie/chat/ChatSettings.h"
#include "zombie/chat/ChatTab.h"
#include "zombie/chat/ChatUtility.h"
#include "zombie/core/Color.h"
#include "zombie/network/chat/ChatType.h"
#include <filesystem>

namespace zombie {
namespace chat {
namespace defaultChats {


class SayChat : public RangeBasedChat {
public:
    public SayChat(ByteBuffer var1, ChatTab var2, IsoPlayer var3) {
      super(var1, ChatType.say, var2, var3);
      if (!this.isCustomSettings()) {
         this.setSettings(getDefaultSettings());
      }
   }

    public SayChat(int var1, ChatTab var2) {
      super(var1, ChatType.say, var2);
      if (!this.isCustomSettings()) {
         this.setSettings(getDefaultSettings());
      }
   }

    public SayChat() {
      super(ChatType.say);
      this.setSettings(getDefaultSettings());
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
      var0.setAllowChatIcons(true);
      var0.setAllowImages(true);
      var0.setAllowFonts(false);
      var0.setAllowBBcode(true);
      var0.setEqualizeLineHeights(true);
      var0.setRange(30.0F);
      var0.setZombieAttractionRange(15.0F);
    return var0;
   }

    ChatMessage createInfoMessage(const std::string& var1) {
    ChatMessage var2 = this.createBubbleMessage(var1);
      var2.setLocal(true);
      var2.setShowInChat(false);
    return var2;
   }

    ChatMessage createCalloutMessage(const std::string& var1) {
    ChatMessage var2 = this.createBubbleMessage(var1);
      var2.setLocal(false);
      var2.setShouldAttractZombies(true);
    return var2;
   }

    std::string getMessageTextWithPrefix(ChatMessage var1) {
      return this.getMessagePrefix(var1) + " " + ChatUtility.parseStringForChatLog(var1.getTextWithReplacedParentheses());
   }
}
} // namespace defaultChats
} // namespace chat
} // namespace zombie
