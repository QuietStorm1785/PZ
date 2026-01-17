#pragma once
#include "zombie/characters/IsoPlayer.h"
#include "zombie/chat/ChatSettings.h"
#include "zombie/chat/ChatTab.h"
#include "zombie/core/Color.h"
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

class ShoutChat : public RangeBasedChat {
public:
public
  ShoutChat(ByteBuffer byteBuffer, ChatTab chatTab, IsoPlayer player) {
    super(byteBuffer, ChatType.shout, chatTab, player);
    if (!this.isCustomSettings()) {
      this.setSettings(getDefaultSettings());
    }
  }

public
  ShoutChat(int int0, ChatTab chatTab) {
    super(int0, ChatType.shout, chatTab);
    if (!this.isCustomSettings()) {
      this.setSettings(getDefaultSettings());
    }
  }

public
  ShoutChat() {
    super(ChatType.shout);
    this.setSettings(getDefaultSettings());
  }

  static ChatSettings getDefaultSettings() {
    ChatSettings chatSettings = new ChatSettings();
    chatSettings.setBold(true);
    chatSettings.setFontColor(new Color(255, 51, 51, 255));
    chatSettings.setShowAuthor(true);
    chatSettings.setShowChatTitle(true);
    chatSettings.setShowTimestamp(true);
    chatSettings.setUnique(true);
    chatSettings.setAllowColors(false);
    chatSettings.setAllowFonts(false);
    chatSettings.setAllowBBcode(false);
    chatSettings.setEqualizeLineHeights(true);
    chatSettings.setRange(60.0F);
    return chatSettings;
  }
}
} // namespace defaultChats
} // namespace chat
} // namespace zombie
