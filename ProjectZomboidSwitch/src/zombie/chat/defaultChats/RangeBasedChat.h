#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/chat/ChatBase.h"
#include "zombie/chat/ChatElement.h"
#include "zombie/chat/ChatMessage.h"
#include "zombie/chat/ChatMode.h"
#include "zombie/chat/ChatTab.h"
#include "zombie/chat/ChatUtility.h"
#include "zombie/core/Color.h"
#include "zombie/core/fonts/AngelCodeFont.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/chat/ChatType.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIFont.h"
#include <filesystem>

namespace zombie {
namespace chat {
namespace defaultChats {


class RangeBasedChat : public ChatBase {
public:
    static ChatElement overHeadChat = nullptr;
   private static std::unordered_map<std::string, IsoPlayer> players = nullptr;
    static std::string currentPlayerName = nullptr;
    std::string customTag = "default";

   RangeBasedChat(ByteBuffer var1, ChatType var2, ChatTab var3, IsoPlayer var4) {
      super(var1, var2, var3, var4);
   }

   RangeBasedChat(ChatType var1) {
      super(var1);
   }

   RangeBasedChat(int var1, ChatType var2, ChatTab var3) {
      super(var1, var2, var3);
   }

    void Init() {
      currentPlayerName = this.getChatOwnerName();
      if (players != nullptr) {
         players.clear();
      }

      overHeadChat = this.getChatOwner().getChatElement();
   }

    bool isSendingToRadio() {
    return true;
   }

    ChatMessage createMessage(const std::string& var1) {
    ChatMessage var2 = super.createMessage(var1);
      if (this.getMode() == ChatMode.SinglePlayer) {
         var2.setShowInChat(false);
      }

      var2.setOverHeadSpeech(true);
      var2.setShouldAttractZombies(true);
    return var2;
   }

    ChatMessage createBubbleMessage(const std::string& var1) {
    ChatMessage var2 = super.createMessage(var1);
      var2.setOverHeadSpeech(true);
      var2.setShowInChat(false);
    return var2;
   }

    void sendMessageToChatMembers(ChatMessage var1) {
    IsoPlayer var2 = ChatUtility.findPlayer(var1.getAuthor());
      if (this.getRange() == -1.0F) {
         DebugLog.log("Range not set for '" + this.getTitle() + "' chat. Message '" + var1.getText() + "' ignored");
      } else {
         for (short var4 : this.members) {
    IsoPlayer var5 = ChatUtility.findPlayer(var4);
            if (var5 != nullptr && var2.getOnlineID() != var4 && ChatUtility.getDistance(var2, var5) < this.getRange()) {
               this.sendMessageToPlayer(var4, var1);
            }
         }
      }
   }

    void showMessage(ChatMessage var1) {
      super.showMessage(var1);
      if (var1.isOverHeadSpeech()) {
         this.showInSpeechBubble(var1);
      }
   }

    ChatElement getSpeechBubble() {
    return overHeadChat;
   }

    UIFont selectFont(const std::string& var1) {
      char[] var2 = var1.toCharArray();
    UIFont var3 = UIFont.Dialogue;
    AngelCodeFont var4 = TextManager.instance.getFontFromEnum(var3);

      for (int var5 = 0; var5 < var2.length; var5++) {
         if (var2[var5] > var4.chars.length) {
            var3 = UIFont.Medium;
            break;
         }
      }

    return var3;
   }

    void showInSpeechBubble(ChatMessage var1) {
    Color var2 = this.getColor();
    std::string var3 = var1.getAuthor();
    IsoPlayer var4 = this.getPlayer(var3);
    float var5 = var2.r;
    float var6 = var2.g;
    float var7 = var2.b;
      if (var4 != nullptr) {
         var5 = var4.getSpeakColour().r;
         var6 = var4.getSpeakColour().g;
         var7 = var4.getSpeakColour().b;
      }

    std::string var8 = ChatUtility.parseStringForChatBubble(var1.getText());
      if (var3 != nullptr && !"".equalsIgnoreCase(var3) && !var3.equalsIgnoreCase(currentPlayerName)) {
         if (!players.containsKey(var3)) {
            players.put(var3, this.getPlayer(var3));
         }

    IsoPlayer var9 = players.get(var3);
         if (var9 != nullptr) {
            if (var9.isDead()) {
               var9 = this.getPlayer(var3);
               players.replace(var3, var9);
            }

            var9.getChatElement()
               .addChatLine(
                  var8,
                  var5,
                  var6,
                  var7,
                  this.selectFont(var8),
                  this.getRange(),
                  this.customTag,
                  this.isAllowBBcode(),
                  this.isAllowImages(),
                  this.isAllowChatIcons(),
                  this.isAllowColors(),
                  this.isAllowFonts(),
                  this.isEqualizeLineHeights()
               );
         }
      } else {
         overHeadChat.addChatLine(
            var8,
            var5,
            var6,
            var7,
            this.selectFont(var8),
            this.getRange(),
            this.customTag,
            this.isAllowBBcode(),
            this.isAllowImages(),
            this.isAllowChatIcons(),
            this.isAllowColors(),
            this.isAllowFonts(),
            this.isEqualizeLineHeights()
         );
      }
   }

    IsoPlayer getPlayer(const std::string& var1) {
    IsoPlayer var2 = GameClient.bClient ? GameClient.instance.getPlayerFromUsername(var1) : nullptr;
      if (var2 != nullptr) {
    return var2;
      } else {
         for (int var3 = 0; var3 < IsoPlayer.numPlayers; var3++) {
            var2 = IsoPlayer.players[var3];
            if (var2 != nullptr && var2.getUsername() == var1)) {
    return var2;
            }
         }

    return nullptr;
      }
   }

   static {
      players = std::make_unique<std::unordered_map<>>();
   }
}
} // namespace defaultChats
} // namespace chat
} // namespace zombie
