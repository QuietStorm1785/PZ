#pragma once
#include "zombie/characters/IsoPlayer.h"
#include "zombie/chat/ChatBase.h"
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

class FactionChat : public ChatBase {
public:
public
  FactionChat(ByteBuffer byteBuffer, ChatTab chatTab, IsoPlayer player) {
    super(byteBuffer, ChatType.faction, chatTab, player);
    if (!this.isCustomSettings()) {
      this.setSettings(getDefaultSettings());
    }
  }

public
  FactionChat(int int0, ChatTab chatTab) {
    super(int0, ChatType.faction, chatTab);
    if (!this.isCustomSettings()) {
      this.setSettings(getDefaultSettings());
    }
  }

  static ChatSettings getDefaultSettings() {
    ChatSettings chatSettings = new ChatSettings();
    chatSettings.setBold(true);
    chatSettings.setFontColor(Color.darkGreen);
    chatSettings.setShowAuthor(true);
    chatSettings.setShowChatTitle(true);
    chatSettings.setShowTimestamp(true);
    chatSettings.setUnique(false);
    return chatSettings;
  }
}
} // namespace defaultChats
} // namespace chat
} // namespace zombie
