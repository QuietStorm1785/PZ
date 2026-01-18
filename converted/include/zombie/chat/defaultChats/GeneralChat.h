#pragma once
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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class GeneralChat : public ChatBase {
public:
 bool discordEnabled = false;
 const Color discordMessageColor = new Color(114, 137, 218);

 public GeneralChat(ByteBuffer byteBuffer, ChatTab chatTab, IsoPlayer player) {
 super(byteBuffer, ChatType.general, chatTab, player);
 if (!this->isCustomSettings()) {
 this->setSettings(getDefaultSettings());
 }
 }

 public GeneralChat(int int0, ChatTab chatTab, bool boolean0) {
 super(int0, ChatType.general, chatTab);
 this->discordEnabled = boolean0;
 if (!this->isCustomSettings()) {
 this->setSettings(getDefaultSettings());
 }
 }

 public GeneralChat() {
 super(ChatType.general);
 }

 static ChatSettings getDefaultSettings() {
 ChatSettings chatSettings = new ChatSettings();
 chatSettings.setBold(true);
 chatSettings.setFontColor(new Color(255, 165, 0);
 chatSettings.setShowAuthor(true);
 chatSettings.setShowChatTitle(true);
 chatSettings.setShowTimestamp(true);
 chatSettings.setUnique(true);
 chatSettings.setAllowColors(true);
 chatSettings.setAllowFonts(true);
 chatSettings.setAllowBBcode(true);
 return chatSettings;
 }

 void sendMessageToChatMembers(ChatMessage chatMessage) {
 if (this->discordEnabled) {
 IsoPlayer player = ChatUtility.findPlayer(chatMessage.getAuthor());
 if (chatMessage.isFromDiscord()) {
 for (short short0 : this->members) {
 this->sendMessageToPlayer(short0, chatMessage);
 }
 } else {
 GameServer.discordBot.sendMessage(chatMessage.getAuthor(), chatMessage.getText());

 for (short short1 : this->members) {
 if (player == nullptr || player.getOnlineID() != short1) {
 this->sendMessageToPlayer(short1, chatMessage);
 }
 }
 }
 } else {
 super.sendMessageToChatMembers(chatMessage);
 }

 DebugLog.log("New message '" + chatMessage + "' was sent members of chat '" + this->getID() + "'");
 }

 void sendToDiscordGeneralChatDisabled() {
 GameServer.discordBot.sendMessage("Server", Translator.getText("UI_chat_general_chat_disabled"));
 }

 std::string getMessagePrefix(ChatMessage chatMessage) {
 StringBuilder stringBuilder = new StringBuilder();
 if (chatMessage.isFromDiscord()) {
 stringBuilder.append(this->getColorTag(this->discordMessageColor);
 } else {
 stringBuilder.append(this->getColorTag());
 }

 stringBuilder.append(" ").append(this->getFontSizeTag()).append(" ");
 if (this->isShowTimestamp()) {
 stringBuilder.append("[").append(LuaManager.getHourMinuteJava()).append("]");
 }

 if (this->isShowTitle()) {
 stringBuilder.append("[").append(this->getTitle()).append("]");
 }

 if (this->isShowAuthor()) {
 stringBuilder.append("[").append(chatMessage.getAuthor()).append("]");
 }

 stringBuilder.append(": ");
 return stringBuilder.toString();
 }

 void packMessage(ByteBufferWriter byteBufferWriter, ChatMessage chatMessage) {
 super.packMessage(byteBufferWriter, chatMessage);
 byteBufferWriter.putBoolean(chatMessage.isFromDiscord());
 }

 ChatMessage unpackMessage(ByteBuffer byteBuffer) {
 ChatMessage chatMessage = super.unpackMessage(byteBuffer);
 if (byteBuffer.get() == 1) {
 chatMessage.makeFromDiscord();
 }

 return chatMessage;
 }
}
} // namespace defaultChats
} // namespace chat
} // namespace zombie
