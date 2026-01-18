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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class AdminChat : public ChatBase {
public:
 public AdminChat(ByteBuffer byteBuffer, ChatTab chatTab, IsoPlayer player) {
 super(byteBuffer, ChatType.admin, chatTab, player);
 if (!this->isCustomSettings()) {
 this->setSettings(getDefaultSettings());
 }
 }

 public AdminChat(int int0, ChatTab chatTab) {
 super(int0, ChatType.admin, chatTab);
 super.setSettings(getDefaultSettings());
 }

 public AdminChat() {
 super(ChatType.admin);
 }

 static ChatSettings getDefaultSettings() {
 ChatSettings chatSettings = new ChatSettings();
 chatSettings.setBold(true);
 chatSettings.setFontColor(Color.white);
 chatSettings.setShowAuthor(true);
 chatSettings.setShowChatTitle(true);
 chatSettings.setShowTimestamp(true);
 chatSettings.setUnique(true);
 chatSettings.setAllowColors(true);
 chatSettings.setAllowFonts(true);
 chatSettings.setAllowBBcode(true);
 return chatSettings;
 }
}
} // namespace defaultChats
} // namespace chat
} // namespace zombie
