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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class SayChat : public RangeBasedChat {
public:
 public SayChat(ByteBuffer byteBuffer, ChatTab chatTab, IsoPlayer player) {
 super(byteBuffer, ChatType.say, chatTab, player);
 if (!this->isCustomSettings()) {
 this->setSettings(getDefaultSettings());
 }
 }

 public SayChat(int int0, ChatTab chatTab) {
 super(int0, ChatType.say, chatTab);
 if (!this->isCustomSettings()) {
 this->setSettings(getDefaultSettings());
 }
 }

 public SayChat() {
 super(ChatType.say);
 this->setSettings(getDefaultSettings());
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
 chatSettings.setAllowChatIcons(true);
 chatSettings.setAllowImages(true);
 chatSettings.setAllowFonts(false);
 chatSettings.setAllowBBcode(true);
 chatSettings.setEqualizeLineHeights(true);
 chatSettings.setRange(30.0F);
 chatSettings.setZombieAttractionRange(15.0F);
 return chatSettings;
 }

 ChatMessage createInfoMessage(const std::string& string) {
 ChatMessage chatMessage = this->createBubbleMessage(string);
 chatMessage.setLocal(true);
 chatMessage.setShowInChat(false);
 return chatMessage;
 }

 ChatMessage createCalloutMessage(const std::string& string) {
 ChatMessage chatMessage = this->createBubbleMessage(string);
 chatMessage.setLocal(false);
 chatMessage.setShouldAttractZombies(true);
 return chatMessage;
 }

 std::string getMessageTextWithPrefix(ChatMessage chatMessage) {
 return this->getMessagePrefix(chatMessage) + " " + ChatUtility.parseStringForChatLog(chatMessage.getTextWithReplacedParentheses());
 }
}
} // namespace defaultChats
} // namespace chat
} // namespace zombie
