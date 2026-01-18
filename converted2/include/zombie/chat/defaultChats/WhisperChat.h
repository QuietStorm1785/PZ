#pragma once
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
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace chat {
namespace defaultChats {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WhisperChat : public ChatBase {
public:
  std::string myName;
  std::string companionName;
  const std::string player1;
  const std::string player2;
  bool isInited = false;

public
  WhisperChat(int int0, ChatTab chatTab, const std::string &string0,
              const std::string &string1) {
    super(int0, ChatType.whisper, chatTab);
    if (!this.isCustomSettings()) {
      this.setSettings(getDefaultSettings());
    }

    this.player1 = string0;
    this.player2 = string1;
  }

public
  WhisperChat(ByteBuffer byteBuffer, ChatTab chatTab, IsoPlayer player) {
    super(byteBuffer, ChatType.whisper, chatTab, player);
    if (!this.isCustomSettings()) {
      this.setSettings(getDefaultSettings());
    }

    this.player1 = GameWindow.ReadString(byteBuffer);
    this.player2 = GameWindow.ReadString(byteBuffer);
  }

  static ChatSettings getDefaultSettings() {
    ChatSettings chatSettings = new ChatSettings();
    chatSettings.setBold(true);
    chatSettings.setFontColor(new Color(85, 26, 139));
    chatSettings.setShowAuthor(true);
    chatSettings.setShowChatTitle(true);
    chatSettings.setShowTimestamp(true);
    chatSettings.setUnique(true);
    chatSettings.setAllowColors(true);
    chatSettings.setAllowFonts(true);
    chatSettings.setAllowBBcode(true);
    return chatSettings;
  }

  std::string getMessagePrefix(ChatMessage chatMessage) {
    if (!this.isInited) {
      this.init();
    }

    StringBuilder stringBuilder = new StringBuilder(this.getChatSettingsTags());
    if (this.isShowTimestamp()) {
      stringBuilder.append("[")
          .append(LuaManager.getHourMinuteJava())
          .append("]");
    }

    if (this.isShowTitle()) {
      stringBuilder.append("[").append(this.getTitle()).append("]");
    }

    if (!this.myName.equalsIgnoreCase(chatMessage.getAuthor())) {
      stringBuilder.append("[").append(this.companionName).append("]");
    } else {
      stringBuilder.append("[to ").append(this.companionName).append("]");
    }

    stringBuilder.append(": ");
    return stringBuilder.toString();
  }

  void packChat(ByteBufferWriter byteBufferWriter) {
    super.packChat(byteBufferWriter);
    byteBufferWriter.putUTF(this.player1);
    byteBufferWriter.putUTF(this.player2);
  }

  std::string getCompanionName() { return this.companionName; }

  void init() {
    if (this.player1 == IsoPlayer.getInstance().getUsername())) {
        this.myName = IsoPlayer.getInstance().getUsername();
        this.companionName = this.player2;
      }
    else {
      if (!this.player2 == IsoPlayer.getInstance().getUsername())) {
          if (Core.bDebug) {
            throw new RuntimeException("Wrong id");
          }

          DebugLog.log("Wrong id in whisper chat. Whisper chat not inited for "
                       "players: " +
                       this.player1 + " " + this.player2);
          return;
        }

      this.myName = IsoPlayer.getInstance().getUsername();
      this.companionName = this.player1;
    }

    this.isInited = true;
  }

public
  static enum ChatStatus { None, Creating, PlayerNotFound; }
}
} // namespace defaultChats
} // namespace chat
} // namespace zombie
