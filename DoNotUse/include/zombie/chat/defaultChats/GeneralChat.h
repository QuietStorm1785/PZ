#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/chat/ChatBase.h"
#include "zombie/chat/ChatMessage.h"
#include "zombie/chat/ChatSettings.h"
#include "zombie/chat/ChatTab.h"
#include "zombie/chat/ChatUtility.h"
#include "zombie/core/Color.h"
#include "zombie/core/Translator.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/chat/ChatType.h"
#include <filesystem>

namespace zombie {
namespace chat {
namespace defaultChats {


class GeneralChat : public ChatBase {
public:
    bool discordEnabled = false;
    const Color discordMessageColor = std::make_shared<Color>(114, 137, 218);

    public GeneralChat(ByteBuffer var1, ChatTab var2, IsoPlayer var3) {
      super(var1, ChatType.general, var2, var3);
      if (!this.isCustomSettings()) {
         this.setSettings(getDefaultSettings());
      }
   }

    public GeneralChat(int var1, ChatTab var2, bool var3) {
      super(var1, ChatType.general, var2);
      this.discordEnabled = var3;
      if (!this.isCustomSettings()) {
         this.setSettings(getDefaultSettings());
      }
   }

    public GeneralChat() {
      super(ChatType.general);
   }

    static ChatSettings getDefaultSettings() {
    ChatSettings var0 = std::make_shared<ChatSettings>();
      var0.setBold(true);
      var0.setFontColor(std::make_shared<Color>(255, 165, 0));
      var0.setShowAuthor(true);
      var0.setShowChatTitle(true);
      var0.setShowTimestamp(true);
      var0.setUnique(true);
      var0.setAllowColors(true);
      var0.setAllowFonts(true);
      var0.setAllowBBcode(true);
    return var0;
   }

    void sendMessageToChatMembers(ChatMessage var1) {
      if (this.discordEnabled) {
    IsoPlayer var2 = ChatUtility.findPlayer(var1.getAuthor());
         if (var1.isFromDiscord()) {
            for (short var4 : this.members) {
               this.sendMessageToPlayer(var4, var1);
            }
         } else {
            GameServer.discordBot.sendMessage(var1.getAuthor(), var1.getText());

            for (short var6 : this.members) {
               if (var2 == nullptr || var2.getOnlineID() != var6) {
                  this.sendMessageToPlayer(var6, var1);
               }
            }
         }
      } else {
         super.sendMessageToChatMembers(var1);
      }

      DebugLog.log("New message '" + var1 + "' was sent members of chat '" + this.getID() + "'");
   }

    void sendToDiscordGeneralChatDisabled() {
      GameServer.discordBot.sendMessage("Server", Translator.getText("UI_chat_general_chat_disabled"));
   }

    std::string getMessagePrefix(ChatMessage var1) {
    std::stringstream var2 = new std::stringstream();
      if (var1.isFromDiscord()) {
         var2.append(this.getColorTag(this.discordMessageColor));
      } else {
         var2.append(this.getColorTag());
      }

      var2.append(" ").append(this.getFontSizeTag()).append(" ");
      if (this.isShowTimestamp()) {
         var2.append("[").append(LuaManager.getHourMinuteJava()).append("]");
      }

      if (this.isShowTitle()) {
         var2.append("[").append(this.getTitle()).append("]");
      }

      if (this.isShowAuthor()) {
         var2.append("[").append(var1.getAuthor()).append("]");
      }

      var2.append(": ");
      return var2;
   }

    void packMessage(ByteBufferWriter var1, ChatMessage var2) {
      super.packMessage(var1, var2);
      var1.putBoolean(var2.isFromDiscord());
   }

    ChatMessage unpackMessage(ByteBuffer var1) {
    ChatMessage var2 = super.unpackMessage(var1);
      if (var1.get() == 1) {
         var2.makeFromDiscord();
      }

    return var2;
   }
}
} // namespace defaultChats
} // namespace chat
} // namespace zombie
