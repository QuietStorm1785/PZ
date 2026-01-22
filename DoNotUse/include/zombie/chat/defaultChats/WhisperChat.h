#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/chat/ChatBase.h"
#include "zombie/chat/ChatMessage.h"
#include "zombie/chat/ChatSettings.h"
#include "zombie/chat/ChatTab.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/chat/ChatType.h"
#include <filesystem>

namespace zombie {
namespace chat {
namespace defaultChats {


class WhisperChat : public ChatBase {
public:
    std::string myName;
    std::string companionName;
    const std::string player1;
    const std::string player2;
    bool isInited = false;

    public WhisperChat(int var1, ChatTab var2, const std::string& var3, const std::string& var4) {
      super(var1, ChatType.whisper, var2);
      if (!this.isCustomSettings()) {
         this.setSettings(getDefaultSettings());
      }

      this.player1 = var3;
      this.player2 = var4;
   }

    public WhisperChat(ByteBuffer var1, ChatTab var2, IsoPlayer var3) {
      super(var1, ChatType.whisper, var2, var3);
      if (!this.isCustomSettings()) {
         this.setSettings(getDefaultSettings());
      }

      this.player1 = GameWindow.ReadString(var1);
      this.player2 = GameWindow.ReadString(var1);
   }

    static ChatSettings getDefaultSettings() {
    ChatSettings var0 = std::make_shared<ChatSettings>();
      var0.setBold(true);
      var0.setFontColor(std::make_shared<Color>(85, 26, 139));
      var0.setShowAuthor(true);
      var0.setShowChatTitle(true);
      var0.setShowTimestamp(true);
      var0.setUnique(true);
      var0.setAllowColors(true);
      var0.setAllowFonts(true);
      var0.setAllowBBcode(true);
    return var0;
   }

    std::string getMessagePrefix(ChatMessage var1) {
      if (!this.isInited) {
         this.init();
      }

    std::stringstream var2 = new std::stringstream(this.getChatSettingsTags());
      if (this.isShowTimestamp()) {
         var2.append("[").append(LuaManager.getHourMinuteJava()).append("]");
      }

      if (this.isShowTitle()) {
         var2.append("[").append(this.getTitle()).append("]");
      }

      if (!this.myName.equalsIgnoreCase(var1.getAuthor())) {
         var2.append("[").append(this.companionName).append("]");
      } else {
         var2.append("[to ").append(this.companionName).append("]");
      }

      var2.append(": ");
      return var2;
   }

    void packChat(ByteBufferWriter var1) {
      super.packChat(var1);
      var1.putUTF(this.player1);
      var1.putUTF(this.player2);
   }

    std::string getCompanionName() {
      return this.companionName;
   }

    void init() {
      if (this.player1 == IsoPlayer.getInstance().getUsername())) {
         this.myName = IsoPlayer.getInstance().getUsername();
         this.companionName = this.player2;
      } else {
         if (!this.player2 == IsoPlayer.getInstance().getUsername())) {
            if (Core.bDebug) {
               throw RuntimeException("Wrong id");
            }

            DebugLog.log("Wrong id in whisper chat. Whisper chat not inited for players: " + this.player1 + " " + this.player2);
            return;
         }

         this.myName = IsoPlayer.getInstance().getUsername();
         this.companionName = this.player1;
      }

      this.isInited = true;
   }
}
} // namespace defaultChats
} // namespace chat
} // namespace zombie
